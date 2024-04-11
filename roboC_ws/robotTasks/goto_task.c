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
static int activate_avoid_opponent = 0;

int get_ball_location(float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float top_sensor_dist, int opp_detected){
    // Returns the location of the detected ball
    // return 0 otherwise
	//THE ORDER OF CHECK MATTERS!  IF NEED ADD SOMETHING ELSE IN THE FUTURE, DONT JUST ADD
    if (mid_sensor_dist <= BALL_THRESHOLD_MID && !opp_detected){
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
    	go_to_target_yaw(ball_yaw, yaw, 0);

        //stop go_to_ball_yaw() when the robot has either faced towards ball_yaw or the ball is already detected
        ball_location = get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, top_sensor_dist, opp_detected);     //get latest ball location
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

    ball_location = get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, top_sensor_dist, opp_detected);     //get latest ball location

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
        if(prev_ball_location == RIGHT){
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
        if(prev_ball_location == LEFT){
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

// /// @brief Alternative GOTO task
// /// @param distance_sensorL
// /// @param distance_sensorR
// /// @param distance_sensorM
// /// @param distance_sensorT
// /// @param detectL_dist
// /// @param detectR_dist
// /// @param detectM_dist
// /// @return SEARCH if opponent detected, SEARCH if back wall detected, GOTO otherwise
// int goto_task_alt(float distance_sensorL, float distance_sensorR, float distance_sensorM, float distance_sensorT, float detectL_dist, float detectR_dist, float detectM_dist){
//     static int goto_state = 0;
//     static float goto_detectL = 0.0;
//     static float goto_detectR = 0.0;
//     static float goto_detectM = 0.0;
//     static float goto_limit = 0.0;
//     // __________
//     //
//     // Updates the detection values
//     // __________

//     if (goto_state == 0){
//         goto_detectL = detectL_dist;
//         goto_detectR = detectR_dist;
//         goto_detectM = detectM_dist;
//         goto_limit = max(max(goto_detectL, goto_detectR), goto_detectM);
//         goto_state = 1;
//     }
//     else{
//         // limit the distance readings, so that it only checks for the ball within the initial search radius
//         distance_sensorL = min(distance_sensorL, goto_limit);
//         distance_sensorR = min(distance_sensorR, goto_limit);
//         distance_sensorM = min(distance_sensorM, goto_limit);
//         distance_sensorT = min(distance_sensorT, goto_limit);

//         if (opponent_detection(distance_sensorT) == 1){
//             goto_state = 0;
//             return SEARCH;
//         }
//         if (detect_back_wall(distance_sensorL, distance_sensorR, distance_sensorM) == TRIGGERED){
//             goto_state = 0;
//             return SEARCH;
//         }
//         // check if ball is detected
//         goto_detectM = detect_ball_mid(distance_sensorM, distance_sensorT);
//         // updates only when low to high
//         if (detect_ball_left(distance_sensorL) > goto_detectL || detect_ball_right(distance_sensorR) > goto_detectR){
//             if (opponent_detection(distance_sensorT) == 0){
//                 goto_detectL = detect_ball_left(distance_sensorL);
//                 goto_detectR = detect_ball_right(distance_sensorR);
//             }
//         }
//     }

//     // __________
//     //
//     // Moves the robot to whatever direction the ball is detected
//     // __________

//     if (goto_detectM <= READY_TO_COLLECT_THRESHOLD){
//         goto_linX = 0.0;
//         goto_angZ = 0.0;
//         goto_state = 0;
//         return COLLECT;
//     }
//     else if (goto_detectM > 0.0){
//         // ball detected in middle, go straight
//         goto_linX = MAX_SPEED;
//         goto_angZ = 0.0;
//     }
//     else {
//         // ball detected on the sides, turn towards the ball
//         float turning_angle = 0.0;
//         float turning_radius = 0.0;
//         float turning_arc = 0.0;
//         float turning_segment = 0.0;
//         float turning_direction = 1.0;
//         if (goto_detectL > 0.0){
//             // ball on left, turn left
//             turning_direction = 1.0;
//             turning_segment = sqrt(pow(goto_detectL, 2) + pow(ROBOT_WIDTH/2.0, 2));
//             turning_angle = 2 * (90.0 - atanDegrees(2 * goto_detectL / ROBOT_WIDTH));
//         }
//         else if (goto_detectR > 0.0){
//             // ball on right, turn right
//             turning_segment = sqrt(pow(goto_detectR, 2) + pow(ROBOT_WIDTH/2.0, 2));
//             turning_angle = 2 * (90.0 - atanDegrees(2 * goto_detectR / ROBOT_WIDTH));
//         }
//         turning_radius = turning_segment / (2 * sinDegrees(turning_angle / 2));
//         turning_arc = turning_radius * turning_angle;

//         float rpmL = calculate_rpmL(turning_arc, turning_direction * turning_angle);
//         float rpmR = calculate_rpmR(turning_arc, turning_direction * turning_angle);
//         float scaled_rpmL = scale_rpmL(rpmL, rpmR);
//         float scaled_rpmR = scale_rpmR(rpmL, rpmR);

//         goto_linX = calculate_linear_x(scaled_rpmL, scaled_rpmR);
//         goto_angZ = calculate_angular_z(scaled_rpmL, scaled_rpmR);
//     }
//     return GOTO;
// }