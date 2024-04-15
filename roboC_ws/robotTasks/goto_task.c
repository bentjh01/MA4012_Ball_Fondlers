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
#define WALL    9

static int ball_location;
static int prev_ball_location;
static float goto_initial_yaw;
static float goto_target_yaw;
static int goto_correction_mode = 0;
static int goto_different_sign;
static float goto_linX;
static float goto_angZ;
static int goto_startup_phase = 1;
static float goto_angular_difference;
static int activate_goto_sweep = 0;
static int goto_sweep_counter = 0;
static int back_to_search_counter = 0;
static int back_to_home_counter = 0;
static int activate_avoid_opponent = 0;
static int activate_wall_protocol = 0;
static int goto_wall_detected;

int get_ball_location(float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float top_sensor_dist, int opp_detected, float yaw){
    // Returns the location of the detected ball
    // return 0 otherwise
    //THE ORDER OF CHECK MATTERS!
    goto_wall_detected = detect_back_wall(left_sensor_dist, right_sensor_dist, mid_sensor_dist);
    if(detect_back_wall(left_sensor_dist, right_sensor_dist, mid_sensor_dist) == TRIGGERED && fabs(yaw) > 170.0){
        return WALL;
    }
    else if (mid_sensor_dist <= BALL_THRESHOLD_MID && !opp_detected){
        return FRONT;
    }
    else if (mid_sensor_dist <= BALL_THRESHOLD_MID && opp_detected && fabs(mid_sensor_dist-top_sensor_dist) <= OPP_DIFFERENTIATION_THRESHOLD){
        return 0;
    }
    else if(mid_sensor_dist <= BALL_THRESHOLD_MID && opp_detected && fabs(mid_sensor_dist-top_sensor_dist) > OPP_DIFFERENTIATION_THRESHOLD){
        return FRONT;
    }
    else if(left_sensor_dist <= BALL_THRESHOLD_LNR && left_sensor_dist <= right_sensor_dist){
  			return LEFT;
  	}
  	else if(right_sensor_dist <= BALL_THRESHOLD_LNR && right_sensor_dist <= left_sensor_dist){
        return RIGHT;
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

void go_to_target_yaw(float target_yaw, float yaw, int move_forward){
    goto_angular_difference = target_yaw - yaw;

    if(goto_angular_difference <= -180) {
    goto_angular_difference = goto_angular_difference+360;
    }
    else if (goto_angular_difference > 180){
        goto_angular_difference = goto_angular_difference-360;
    }

    goto_linX = move_forward * GOTO_CURVE_LIN_SPEED;
    goto_angZ = GOTO_ALIGN_BALL_GAIN * goto_angular_difference;
    if(fabs(goto_angZ) < 15.0){
    	goto_angZ = sgn(goto_angZ)*15.0;
    }
    return;
}

void goto_sweep(){
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
        goto_sweep_counter += 1;
    }
    return;
}

int avoid_opponent(){
	if(back_to_search_counter < round(1.0/DT_MAIN)){
		goto_linX = -0.3;
    goto_angZ = 90.0;
    back_to_search_counter += 1;
    return GOTO;
  }
  else{
  	goto_startup_phase = 1;
  	activate_avoid_opponent = 0;
  	return SEARCH;
  }
}

int goto_task(float x, float y, float yaw, float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float top_sensor_dist, int opp_detected, float ball_yaw){
    //turn to ball_yaw when first started
    if(goto_startup_phase){
    	back_to_search_counter = 0;
    	go_to_target_yaw(ball_yaw, yaw, 1);

        //stop go_to_target_yaw() when the robot has either faced towards ball_yaw or the ball is already detected
        ball_location = get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, top_sensor_dist, opp_detected, yaw);     //get latest ball location
	    if(fabs(yaw-ball_yaw) <= YAW_TOLERANCE || ball_location != 0){
	    	goto_startup_phase = 0;
		    goto_linX = 0.0;
        	goto_angZ = 0.0;

	    	//check if sweep is needed (needed when already reached ball_yaw, but no detections are ever found)
	    	if(ball_location == 0){
                //initialize sweeping movement
	    		goto_sweep_counter = 0;
	    		activate_goto_sweep = 1;
	    		goto_linX = 0.0;
        		goto_angZ = -15.0;
	    	}
	    }
    	return GOTO;
    }

    if(activate_avoid_opponent){
    	return avoid_opponent();
    }

    //WALL
    if(activate_wall_protocol){
    	go_to_target_yaw(0, yaw, -1);

    	if(fabs(yaw) < YAW_TOLERANCE){
    		return HOME;
    	}
    	return GOTO;
    }

    ball_location = get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, top_sensor_dist, opp_detected, yaw);     //get latest ball location

    //sweep until something is detected
    if(activate_goto_sweep){
    	//check for ball
    	if(ball_location != 0){
    		goto_linX = 0.0;
        	goto_angZ = 0.0;
    		activate_goto_sweep = 0;
    		return GOTO;
    	}

    	//sweep
    	goto_sweep();
        //return to search if after sweeping nothing is found
        if(goto_sweep_counter > round(3.0*GOTO_SWEEP_TIME/DT_MAIN)){
            goto_linX = 0.0;
            goto_angZ = 0.0;
            activate_goto_sweep = 0;
            return SEARCH;
        }
    	return GOTO;
    }

    //correction mode activated, go to the middle yaw
    if(goto_correction_mode){
        go_to_target_yaw(goto_target_yaw, yaw, 1);

        //When approximately facing towards the ball or ball is detected by middle sensor
        if(fabs(yaw-goto_target_yaw) < YAW_TOLERANCE || (ball_location == FRONT && !opp_detected)){
            //move forward
            goto_linX = 0.20;
            goto_angZ = 0.0;
	        	goto_correction_mode = 0;
	        	back_to_search_counter = 0; //reset counter, give goto more time
        }
        return GOTO;
    }

    //Check if there is new detection that is different from the previous
    if(ball_location != 0 && prev_ball_location != ball_location){
        prev_ball_location = ball_location; //save prev ball location
    }

    //Do different things when detecting a ball in different positions
    if(ball_location == 0 && opp_detected){ //Opponent, not ball
        back_to_search_counter = 0;
        activate_avoid_opponent = 1;
        return GOTO;

    		/*//stop movement
        goto_linX = -0.1;
        goto_angZ = 90.0;
        goto_startup_phase = 1;
        return SEARCH;*/
    }
    else if(ball_location == WALL){

        back_to_search_counter = 0;
        back_to_home_counter = 0;
        activate_wall_protocol = 1;
    	// back_to_home_counter += 1;

    	// if(back_to_home_counter > round(0.2/DT_MAIN)){
        //     back_to_search_counter = 0;
        //     back_to_home_counter = 0;
    	// 	activate_wall_protocol = 1;
    	// }
    	return GOTO;
    }
    else if(ball_location == FRONT){ //Ball in front, check if need to move forward to get closer to the ball
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
    else if(ball_location == LEFT){ //Ball on the left
        //if ball previously detected on the right, now detected on to the left. Meaning the ball is too far for the middle sensor to pick up.
        //if(prev_ball_location == RIGHT){
        if(0 == 1){ //testing code to deactivate correction_mode
            //activate correction mode
            goto_correction_mode = 1;
            goto_target_yaw = calculate_goto_target_yaw(goto_initial_yaw, yaw);
            return GOTO;
        }
        else{ //ball detected on the left for the first time
            //record yaw and rotate CCW
            goto_initial_yaw = yaw;
            goto_linX = GOTO_CURVE_LIN_SPEED;
            goto_angZ = GOTO_CURVE_ANG_SPEED;
            return GOTO;
        }
    }
    else if(ball_location == RIGHT){ //Ball on the right
        //if ball previously detected on the left, now detected on to the right. Meaning the ball is too far for the middle sensor to pick up.
        //if(prev_ball_location == LEFT){
        if(0 == 1){ //testing code to deactivate correction_mode
            //activate correction mode
            goto_correction_mode = 1;
            goto_target_yaw = calculate_goto_target_yaw(goto_initial_yaw, yaw);
	        return GOTO;
        }
        else{ //ball detected on the right for the first time
            //record yaw and rotate CW
            goto_initial_yaw = yaw;
            goto_linX = GOTO_CURVE_LIN_SPEED;
            goto_angZ = -GOTO_CURVE_ANG_SPEED;
            return GOTO;
        }
    }
    else{ //ball_location == 0
    	back_to_search_counter += 1;

    	if(back_to_search_counter > BACK_TO_SEARCH_COUNT){
    		goto_startup_phase = 1;
    		return SEARCH;
    	}
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
