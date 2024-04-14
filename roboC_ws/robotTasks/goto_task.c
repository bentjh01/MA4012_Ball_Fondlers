#include "../config.h"

// @ShaDowFrost2417

/*
1. approach the ball and keep it centered
2. if at any point, the ball turns out to be an opponent, return to search_task
3. if ball is in collection point, return to collect_task
*/

float goto_linX;
float goto_angZ;

int goto_task_alt(float distanceL, float distanceR, float distanceM, float case_num){
    /// GOTO Task
    /// 1. Limits the goto distance to the initial detected ball distance
    /// 2. Uses the distance sensors to detect the ball within this limit 
    /// 3. Moves the robot to the ball using the differential drive kinematics
    /// 4. Returns to SEARCH if opponent detected or robot has travelled too far
    /// 5. Returns to COLLECT if ball is detected within the collection threshold
    static int goto_startup = 1;
    static float goto_limit;
    static float goto_timeout;
    static int last_ball_position; 

    if (goto_startup == 1){
        goto_timeout = 0;
        goto_startup = 0;
        if (case_num == BALL_LEFT_DETECTED){
            last_ball_position = BALL_LEFT_DETECTED;
            goto_limit = distanceL * 1.2;
        }
        if (case_num == BALL_RIGHT_DETECTED){
            last_ball_position = BALL_RIGHT_DETECTED;
            goto_limit = distanceR * 1.2;
        }
    }
    
    // check if ball is detected
    int test_detect = detect_ball_2(distanceL, distanceR, distanceM, distanceM, goto_limit);
    // Last ball location on LEFT
    if (last_ball_position == BALL_LEFT_DETECTED && test_detect == BALL_RIGHT_DETECTED){
        last_ball_position = BALL_RIGHT_DETECTED;
    }
    // Last ball location on RIGHT
    else if (last_ball_position == BALL_RIGHT_DETECTED && test_detect == BALL_LEFT_DETECTED){
        last_ball_position = BALL_LEFT_DETECTED;
    }

    if (case_num == WALL_DETECTED || case_num == OPPONENT_DETECTED){
        goto_startup = 1;
        return HOME;
    }

    goto_timeout++;
    if (goto_timeout > GOTO_TIMEOUT){
        goto_startup = 1;
        return SEARCH;
    }

    // __________
    //
    // Moves the robot to whatever direction the ball is detected
    // __________

    if (distanceM < READY_TO_COLLECT_THRESHOLD){
        goto_linX = MAX_SPEED;
        goto_angZ = 0.0;
        goto_startup = 1;
        return COLLECT;
    }
    else if (test_detect == BALL_MIDDLE_DETECTED){
        // ball detected in middle, go straight
        goto_linX = MAX_SPEED;
        goto_angZ = 0.0;
    }
    else {
        // ball detected on the sides, turn towards the ball
        float turning_direction = 1.0;
        if (last_ball_position == BALL_LEFT_DETECTED){
            // ball on left, turn left
            turning_direction = 1.0;
        }
        else if (last_ball_position == BALL_RIGHT_DETECTED){
            // ball on right, turn right
            turning_direction = -1.0;
        }
        goto_linX = MAX_SPEED * goto_limit/100.0;
        goto_angZ = turning_direction * MAX_TURN * 0.4;
    }
    return GOTO;
}

/// @return linear velocity in m/s
float get_goto_linX(){
    return goto_linX;
}

/// @brief Function to get the angular velocity for the search task
/// @return angular velocity in deg/s
float get_goto_angZ(){
    return goto_angZ;
}

