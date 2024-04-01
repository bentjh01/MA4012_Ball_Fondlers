#include "../config.h"

// @ShaDowFrost2417

/*
1. approach the ball and keep it centered
2. if at any point, the ball turns out to be an opponent, return to search_task
3. if ball is in collection point, return to collect_task
*/

#define FRONT   1
#define LEFT    2
#define RIGHT   3

static int ball_location;
static int prev_ball_location;
static float goto_initial_yaw;
static float goto_current_yaw;
static float goto_target_yaw;
static int goto_correction_mode = 0;
static int goto_different_sign;

int goto_opponent_detected(float short_sensor_dist){
    //may need to move this to components into sensors.c
    if(short_sensor_dist <= OPP_CLOSENESS_THRESHOLD){
        //Theres an opp robot close in front
        return OPP_DETECTED;
    }
    else{
        return 0;
    }
}

int get_ball_location(float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float short_sensor_dist){
    // Returns the location of the detected ball
    // return 0 otherwise
    if (left_sensor_dist <= BALL_THRESHOLD_LNR && left_sensor_dist <= right_sensor_dist){
        return LEFT;
    }
    else if(right_sensor_dist <= BALL_THRESHOLD_LNR && right_sensor_dist <= left_sensor_dist){
        return RIGHT;
    }
    else if(mid_sensor_dist <= BALL_THRESHOLD_MID && goto_opponent_detected(short_sensor_dist) == 0){
        return FRONT;
    }
    else{
        return 0;
    }
}

float calculate_goto_target_yaw(float goto_initial_yaw, float yaw){
    goto_different_sign = (goto_initial_yaw < 0 && yaw > 0) || (goto_initial_yaw > 0 && yaw < 0);
    if(goto_different_sign && fabs(goto_initial_yaw) > 90 && fabs(yaw) > 90){
        //special calculation since the yaw jumps from 180 to -180
        if((goto_initial_yaw + yaw + 360.0)/2.0 > 180){
            return ((goto_initial_yaw + yaw + 360.0)/2.0) - 360.0;
        }
        else{
            return (goto_initial_yaw + yaw + 360.0)/2.0;
        }
    }
    else{
        return (goto_initial_yaw + yaw)/2.0;
    }
}

int goto_task(float x, float y, float yaw, float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float short_sensor_dist){
    ball_location = get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, short_sensor_dist);     //get latest ball location

    //Check if new detection there is new detection that is different from the previous (Cos if e.g. detect left, then left again, can be 2 different balls)
    if(get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, short_sensor_dist) != 0 && prev_ball_location != ball_location){
        robot_move(linear_velocity = 0, angular_velocity = 0);  //stop movement
        prev_ball_location = ball_location;                     //save prev ball location
    }

    if(ball_location == FRONT && goto_opponent_detected(short_sensor_dist) == OPP_DETECTED){
        //Opponent, not ball
        robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
        return SEARCH_BALL;
    }
    else if(ball_location == FRONT && mid_sensor_dist > READY_TO_COLLECT_THRESHOLD && goto_opponent_detected(short_sensor_dist) != OPP_DETECTED){
        //Ball in front, check if need to move forward to get closer to the ball
        if(mid_sensor_dist > READY_TO_COLLECT_THRESHOLD){
            robot_move(linear_velocity = 50, angular_velocity = 0); //move forward
            return GOTO_BALL;
        }
        else{
            robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
            return COLLECT_BALL;
        }
    }
    else if(ball_location == LEFT){
        //Ball on the left
        //if ball previously detected on the right, now detected on to the left. Meaning the ball is too far for the middle sensor to pick up.
        if(prev_ball_location == RIGHT){
            goto_correction_mode = 1;                                           //activate correction mode
            goto_target_yaw = calculate_goto_target_yaw(goto_initial_yaw, yaw); //calculate target yaw (approximate where the ball is)
        }

        //correction mode activated, go to the 
        if(goto_correction_mode){
            robot_move(linear_velocity = 0, angular_velocity = -20);    //rotate CW

            //When approximately facing towards the ball
            if(fabs(yaw-goto_target_yaw) < GOTO_YAW_TOLERANCE){
                robot_move(linear_velocity = 20, angular_velocity = 0); //move forward
            }
            return GOTO_BALL;
        }
        //ball detected on the left for the first time
        else{
            goto_initial_yaw = yaw;
            robot_move(linear_velocity = 0, angular_velocity = 20); //rotate CCW
            return GOTO_BALL;
        }
    }
    else if(ball_location == RIGHT){
        //Ball on the right
        //if ball previously detected on the left, now detected on to the right. Meaning the ball is too far for the middle sensor to pick up.
        if(prev_ball_location == LEFT){
            goto_correction_mode = 1;                                           //activate correction mode
            goto_target_yaw = calculate_goto_target_yaw(goto_initial_yaw, yaw); //calculate target yaw (approximate where the ball is)
        }

        //correction mode activated, go to the 
        if(goto_correction_mode){
            robot_move(linear_velocity = 0, angular_velocity = 20);    //rotate CCW

            //When approximately facing towards the ball
            if(fabs(yaw-goto_target_yaw) < GOTO_YAW_TOLERANCE){
                robot_move(linear_velocity = 20, angular_velocity = 0); //move forward
            }
            return GOTO_BALL;
        }
        //ball detected on the left for the first time
        else{
            goto_initial_yaw = yaw;
            robot_move(linear_velocity = 0, angular_velocity = -20); //rotate CW
            return GOTO_BALL;
        }
    }
    else{
        return GOTO_BALL;
    }




    ////////////////////////////////////////////
    //ROTATE UNTIL MIDDLE, MOVE FORWARD
    if (success == 1){
        return COLLECT_BALL;
    }
    else if (goto_opponent_detected){
        return SEARCH_BALL;
    }
    else{
        return GOTO_BALL;
    }
}