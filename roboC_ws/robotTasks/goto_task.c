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
static float goto_linX;
static float goto_angZ;
static int goto_startup_phase = 1;
static float goto_angular_difference;
static int activate_goto_sweep = 0;
static int goto_sweep_counter = 0;

// int goto_opponent_detected(float short_sensor_dist){
//     //may need to move this to components into sensors.c
//     if(short_sensor_dist <= OPP_CLOSENESS_THRESHOLD){
//         //Theres an opp robot close in front
//         return OPP_DETECTED;
//     }
//     else{
//         return 0;
//     }
// }

int get_ball_location(float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, int opp_detected){
    // Returns the location of the detected ball
    // return 0 otherwise
    if (left_sensor_dist <= BALL_THRESHOLD_LNR && left_sensor_dist <= right_sensor_dist){
        return LEFT;
    }
    else if(right_sensor_dist <= BALL_THRESHOLD_LNR && right_sensor_dist <= left_sensor_dist){
        return RIGHT;
    }
    else if(mid_sensor_dist <= BALL_THRESHOLD_MID && !opp_detected){
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

int goto_task(float x, float y, float yaw, float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, int opp_detected, float ball_yaw){
    //turn to ball_yaw when first started
    if(goto_startup_phase){
    	goto_angular_difference = ball_yaw - yaw;

    	if(goto_angular_difference <= -180) {
        goto_angular_difference = goto_angular_difference+360;
      }
      else if (goto_angular_difference > 180){
      	goto_angular_difference = goto_angular_difference-360;
      }

      goto_linX = 0.0;
      goto_angZ = GOTO_ALIGN_BALL_GAIN * goto_angular_difference;
	    
      ball_location = get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, opp_detected);     //get latest ball location
	    
	    if(fabs(yaw-ball_yaw) <= YAW_TOLERANCE || ball_location != 0){
	    	goto_startup_phase = 0;
		goto_linX = 0.0;
        	goto_angZ = 0.0;
	    	
	    	//check if sweep is needed
	    	if(ball_location == 0){
	    		goto_sweep_counter = 0;
	    		activate_goto_sweep = 1;
	    		goto_linX = 0.0;
        	goto_angZ = -15.0;
	    	}
	    }
    	return GOTO;
    }

    ball_location = get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, opp_detected);     //get latest ball location

    //if no detection even after going to the supposed ball_yaw
    if(activate_goto_sweep){
    	//sweep until something is detected
    	//check for ball
    	if(ball_location != 0){
    		goto_linX = 0.0;
        goto_angZ = 0.0;
    		activate_goto_sweep = 0;
    		return GOTO;
    	}
    	
    	//sweep
    	if(goto_angZ < 0.0){
    		if(goto_sweep_counter < round(GOTO_SWEEP_TIME/DT_MAIN)){
    			goto_sweep_counter += 1;
    		}
    		else{
    			goto_linX = 0.0;
        	goto_angZ = 15.0;
    		}
    	}
    	else{
    		if(goto_sweep_counter < round(3.0*GOTO_SWEEP_TIME/DT_MAIN)){
    			goto_sweep_counter += 1;
    		}
    		else{
    			goto_linX = 0.0;
        	goto_angZ = 0.0;
        	activate_goto_sweep = 0;
        	return SEARCH;
    		}
    	}
    	return GOTO;
    }

    //correction mode activated, go to the middle yaw
    if(goto_correction_mode != 0){
        //rotate depending on correction mode
        goto_linX = 0.20;
        goto_angZ = goto_correction_mode*15.0;

        //When approximately facing towards the ball
        if(fabs(yaw-goto_target_yaw) < YAW_TOLERANCE || (ball_location == FRONT && !opp_detected)){
            //move forward
            goto_linX = 0.20;
            goto_angZ = 0.0;
	    goto_correction_mode = 0;
	}
	return GOTO;
    }

    //Check if there is new detection that is different from the previous (Cos if e.g. detect left, then left again, can be 2 different balls)
    if(ball_location != 0 && prev_ball_location != ball_location){
        prev_ball_location = ball_location; //save prev ball location
    }

    if(ball_location == FRONT && opp_detected){
        //Opponent, not ball
        //stop movement
        goto_linX = 0.0;
        goto_angZ = 0.0;
        goto_startup_phase = 1;
        return SEARCH;
        //return GOTO;
    }
    else if(ball_location == FRONT && !opp_detected){
        //Ball in front, check if need to move forward to get closer to the ball
        if(mid_sensor_dist > READY_TO_COLLECT_THRESHOLD){
            //move forward
            goto_linX = 0.20;
            goto_angZ = 0.0;
            return GOTO;
        }
        else{
            //slow forward and pass to collect_task
            goto_linX = 0.1;
            goto_angZ = 0.0;
            goto_startup_phase = 1;
            return COLLECT;
        }
    }
    else if(ball_location == LEFT){
        //Ball on the left
        //if ball previously detected on the right, now detected on to the left. Meaning the ball is too far for the middle sensor to pick up.
        if(prev_ball_location == RIGHT){
            goto_correction_mode = 1;                                           //activate correction mode
            goto_target_yaw = calculate_goto_target_yaw(goto_initial_yaw, yaw); //calculate target yaw (approximate where the ball is)
	    return GOTO;
        }
        else{
	    //ball detected on the left for the first time
            goto_initial_yaw = yaw;
            //rotate CCW
            goto_linX = 0.20;
            goto_angZ = 15.0;
            return GOTO;
        }
    }
    else if(ball_location == RIGHT){
        //Ball on the right
        //if ball previously detected on the left, now detected on to the right. Meaning the ball is too far for the middle sensor to pick up.
        if(prev_ball_location == LEFT){
            goto_correction_mode = -1;                                           //activate correction mode
            goto_target_yaw = calculate_goto_target_yaw(goto_initial_yaw, yaw); //calculate target yaw (approximate where the ball is)
	    return GOTO;
        }
        else{
	    //ball detected on the right for the first time
            goto_initial_yaw = yaw;
            //rotate CW
            goto_linX = 0.20;
            goto_angZ = -15.0;
            return GOTO;
        }
    }
    else{ //ball_location == 0
        return GOTO;
    }
}

/// @brief Function to get the linear for the search task
/// @return linear velocity in m/s
float get_goto_linX(){
    return goto_linX;
}

/// @brief Function to get the angular velocity for the search task
/// @return angular velocity in deg/s
float get_goto_angZ(){
    return goto_angZ;
}
