#include "../config.h"
#include "../components/motor_control.c"
#include "../components/controller.c"
#include "../components/motor.c"
#include "../components/sensors.c"

// @FANZIFU

static float edge_linX = 0.0;
static float edge_angZ = 0.0;
static int edge_line_case;

static float edge_goal_yaw = 0.0;
static float edge_x = 0.0;
static float edge_y = 0.0;
static float edge_linX_sign = 1;
// static float EDGE_REVERSE_DISTANCE = 0.0;

/// @brief Detects if a line sensor is triggered
/// @param FL Front Left sensor
/// @param BL Back Left sensor
/// @param BR Back Right sensor
/// @param FR Front Right sensor
/// @return returns TRIGGERED if a sensor is triggered, NOT_TRIGGERED otherwise
int edge_detected(int FL, int BL, int BR, int FR){
	if (FL == TRIGGERED || BL == TRIGGERED || BR == TRIGGERED || FR == TRIGGERED){
		edge_line_case = FL*1000 + BL*100 + BR*10 + FR;
		return TRIGGERED;
	}
	else{
		return NOT_TRIGGERED;
	}
}

// /// @brief Determines the goal yaw based on the robot's current yaw and the sensor that is triggered
// /// @param rb_x robot's x position
// /// @param rb_yaw robot's yaw
// /// @param FL Front Left sensor
// /// @param FR Front Right sensor
// /// @param BL Back Left sensor
// /// @param BR Back Right sensor
// void avoid_case_check(float rb_x, float rb_y, float rb_yaw, int FL, int FR, int BL, int BR){
// 	float alpha;
// 	float rotate_ang;
// 	edge_x = rb_x;
// 	edge_y = rb_y;

// 	// FL or FR is detected, BL and BR are not detected
// 	if ((FL == TRIGGERED || FR == TRIGGERED) && (BL == NOT_TRIGGERED && BR == NOT_TRIGGERED)){
// 		edge_linX_sign = -1;
// 		// robot facing deliver wall
// 		if (rb_yaw >= -175 && rb_yaw < -95) {
// 			// wall on right, turn left
// 			if (FR == TRIGGERED && FL == NOT_TRIGGERED){
// 				//alpha = 180 - rb_yaw;
// 				alpha = 180 - fabs(rb_yaw); //Bryan: if the above alpha doesnt work, might be this bottom one instead
// 				rotate_ang = (180 - 2*alpha) * (1);
// 			}
// 			// wall on left, turn right
// 			else if (FR == NOT_TRIGGERED && FL == TRIGGERED) {
// 				//alpha = rb_yaw - 90;
// 				alpha = fabs(rb_yaw) - 90; //Bryan: if the above alpha doesnt work, might be this bottom one instead
// 				rotate_ang = (180 - 2*alpha) * (-1);
// 			}

// 		// facing right wall at right wall
// 		} else if (rb_yaw >= -95 && rb_yaw < -85) {
// 			if (rb_x >= 1.2){
// 				// turn towards the delivery wall
// 				rotate_ang = -90;
// 			}else {
// 				rotate_ang = 90;
// 			}

// 		// robot facing far wall
// 		} else if (rb_yaw >= -85 && rb_yaw < -5) {
// 			// robot at right wall
// 			if (FR == TRIGGERED && FL == NOT_TRIGGERED){
// 				//alpha = 90 - rb_yaw;
// 				alpha = 90 - fabs(rb_yaw); //Bryan: if the above alpha doesnt work, might be this bottom one instead
// 				rotate_ang = (180 - 2*alpha) * (1);
// 			} // robot at far wall
// 			else if (FR == NOT_TRIGGERED && FL == TRIGGERED) {
// 				//alpha = rb_yaw;
// 				alpha = fabs(rb_yaw); //Bryan: if the above alpha doesnt work, might be this bottom one instead
// 				rotate_ang = (180 - 2*alpha) * (-1);
// 			}

// 		// robot at far wall
// 		} else if (rb_yaw >= -5 && rb_yaw < 5) {
// 			rotate_ang = -180;

// 		// robot facing far wall
// 		} else if (rb_yaw >= 5 && rb_yaw < 85) {
// 			// robot at far wall
// 			if (FR == TRIGGERED && FL == NOT_TRIGGERED){
// 				alpha = rb_yaw;
// 				rotate_ang = (180 - 2*alpha) * (1);
// 			}
// 			// robot at left wall
// 			else if (FR == NOT_TRIGGERED && FL == TRIGGERED) {
// 				alpha = 90 - rb_yaw;
// 				rotate_ang = (180 - 2*alpha) * (-1);
// 			}
// 		// robot facing left wall
// 		} else if (rb_yaw >= 85 && rb_yaw < 95) {
// 			// turn towards the delivery wall
// 			if (rb_x >= 1.2){
// 				rotate_ang = 90;
// 			}else {
// 				rotate_ang = -90;
// 			}
// 		// robot facing delivery wall
// 		} else if (rb_yaw >= 95 && rb_yaw < 175) {
// 			// robot at left wall
// 			if (FR == TRIGGERED && FL == NOT_TRIGGERED){
// 				alpha = rb_yaw - 90;
// 				rotate_ang = (180 - 2*alpha) * (1);
// 			}
// 			// robot at delivery wall
// 			else if (FR == NOT_TRIGGERED && FL == TRIGGERED) {
// 				alpha = 180 - rb_yaw;
// 				rotate_ang = (180 - 2*alpha) * (-1);
// 			}
// 		// robot facing delivery wall and at delivery wall
// 		} else if (rb_yaw > 175 && rb_yaw <= -175) {
// 			rotate_ang = -180;
// 		}

// 		edge_goal_yaw = wrap_to_pi(rb_yaw + rotate_ang);
// 		return;
// 	}
// 	//status 2: only backward sensors detetcted
// 	else if((BL == TRIGGERED || BR == TRIGGERED) && (FL == NOT_TRIGGERED && FR == NOT_TRIGGERED)){
// 		edge_goal_yaw = 0.0;
// 		edge_linX_sign = 1;
// 		return;
// 	}
// 	//Some special cases: in corner
// 	else{
// 		edge_goal_yaw = wrap_to_pi(rb_yaw+15.0);
// 		//return;
// 	}
// 	// Define the reverse distance
// 	if (rb_x < 60){
// 		EDGE_REVERSE_DISTANCE = EDGE_REVERSE_DISTANCE_BIG;
// 	} else {
// 		EDGE_REVERSE_DISTANCE = EDGE_REVERSE_DISTANCE_SMALL;
// 	}
// 	return;
// }

// /// @brief Performs edge avoidance
// /// @param rb_x robot's x position
// /// @param rb_y robot's y position
// /// @param rb_yaw robot's current yaw
// /// @return the previous task if successful, EDGE otherwise

// int edge_avoid_task(float rb_x, float rb_y, float rb_yaw, int prev_task){
// 	float distance_from_edge = calculate_distance(rb_x, rb_y, edge_x, edge_y);
// 	float yaw_error = edge_goal_yaw - rb_yaw;

//     // Correcting the error when trasition -s180
//     if (yaw_error <= -180.0){
//         yaw_error += 360.0;
//     }
//     else if (yaw_error > 180.0){
//         yaw_error -= 360.0;
//     }

// 	if (distance_from_edge > EDGE_REVERSE_DISTANCE && abs(yaw_error) < YAW_TOLERANCE){
// 	//if (rev_counter > 25){
// 		edge_linX = 0.0;
// 		edge_angZ = 0.0;
// 		return prev_task;
// 	}
// 	else if (distance_from_edge < EDGE_REVERSE_DISTANCE){
// 	//else if (rev_counter < 25){
// 		//edge_linX = edge_linX_sign * distance_from_edge * 1.2;// MAX_SPEED;
// 		edge_linX = edge_linX_sign * 0.3;
// 		//edge_linX = edge_linX_sign * MAX_SPEED;
// 		//edge_linX = MAX_SPEED;
// 		//edge_angZ = 0.0;
// 		//return EDGE;
// 	}
// 	else if (fabs(yaw_error) > YAW_TOLERANCE){
// 		//edge_linX = 0.0;
// 		// edge_angZ = EDGE_YAW_KP * yaw_error;
// 		edge_angZ = 30.0 * sgn(yaw_error);
// 		//return EDGE;
// 	}
// 	return EDGE;
// }

/// @brief Fetches the commanded linear velocity
/// @return linear velocity [m/s]
float get_edge_avoid_linX(){
	return edge_linX;
}

/// @brief Fetches the commanded angular velocity
/// @return angluar velocity [deg/s]
float get_edge_avoid_angZ(){
	return edge_angZ;
}

int get_edge_line_case(){
	return edge_line_case;
}


float edge_sgn_linX = 1.0;
float edge_sgn_angZ = 1.0;
void avoid_case_check_alt(float rb_x, float rb_y, float rb_yaw, int FL, int FR, int BL, int BR){
	float sgn_linX = 1.0;
	float sgn_angZ = 1.0;
	// FRONT SENSORS
	if (FL == TRIGGERED || FR == TRIGGERED){
		edge_sgn_linX = -1.0;
	}
	else{
		edge_sgn_linX = 1.0;
	}
	if (FL == TRIGGERED || BL == TRIGGERED){
		edge_sgn_angZ = -1.0;
	}
	else {
		edge_sgn_angZ = 1.0;
	}
	edge_x = rb_x;
	edge_y = rb_y;
}

int edge_avoid_alt_task(float rb_x, float rb_y, float rb_yaw, int prev_task){
	float distance_from_edge = calculate_distance(edge_x, edge_y, rb_x, rb_y);
	if (distance_from_edge <= EDGE_REVERSE_DISTANCE_BIG){
		edge_linX = edge_sgn_linX * MAX_SPEED;
		edge_angZ = 0.0;
	}
	else{
		if (count_move_rotate(90.0, MAX_TURN) == FAIL){
			edge_linX = 0.0;
			edge_angZ = edge_sgn_angZ * MAX_TURN;
		}
		else {
			return prev_task;
		}
	}
	return EDGE;
}