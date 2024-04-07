#include "../config.h"
#include "../components/motor_control.c"
#include "../components/controller.c"
#include "../components/motor.c"
#include "../components/sensors.c"

// @FANZIFU

static float edge_linX = 0.0;
static float edge_angZ = 0.0;
static float edge_goal_yaw = 0.0;
static float edge_x = 0.0;
static float edge_y = 0.0;
static float edge_linX_sign = 1;

/// @brief Detects if a line sensor is triggered
/// @param FL Front Left sensor
/// @param BL Back Left sensor
/// @param BR Back Right sensor
/// @param FR Front Right sensor
/// @return returns TRIGGERED if a sensor is triggered, NOT_TRIGGERED otherwise
int edge_detected(int FL, int BL, int BR, int FR){
	if (FL == TRIGGERED){
		return TRIGGERED;
	}
	if (BL == TRIGGERED){
		return TRIGGERED;
	}
	if (BR == TRIGGERED){
		return TRIGGERED;
	}
	if (FR == TRIGGERED){
		return TRIGGERED;
	}
	return NOT_TRIGGERED;
}

/// @brief Determines the goal yaw based on the robot's current yaw and the sensor that is triggered
/// @param rb_x robot's x position
/// @param rb_yaw robot's yaw
/// @param FL Front Left sensor
/// @param FR Front Right sensor
/// @param BL Back Left sensor
/// @param BR Back Right sensor
void avoid_case_check(float rb_x, float rb_y, float rb_yaw, int FL, int FR, int BL, int BR){
	float alpha;
	float rotate_ang;
	edge_x = rb_x;
	edge_y = rb_y;
	//status 1: forward sensor detetcted

	// FL or FR is detected, BL and BR are not detected
	if ((FL == 1 || FR == 1) && (BL != 1 && BR != 1)){
		edge_linX_sign = -1;
		// robot facing deliver wall
		if (rb_yaw >= -175 && rb_yaw < -95) {
			// wall on right, turn left
			if (FR == 1 && FL == 0){
				alpha = 180 - rb_yaw;
				rotate_ang = (180 - 2*alpha) * (1);
			} 
			// wall on left, turn right
			else if (FR == 0 && FL == 1) {
				alpha = rb_yaw - 90;
				rotate_ang = (180 - 2*alpha) * (-1);
			}

		// facing right wall at right wall
		} else if (rb_yaw >= -95 && rb_yaw < -85) {
			if (rb_x >= 1.2){
				// turn towards the delivery wall
				rotate_ang = -90;
			}else {
				rotate_ang = 90;
			}

		// robot facing far wall
		} else if (rb_yaw >= -85 && rb_yaw < -5) {
			// robot at right wall
			if (FR == 1 && FL == 0){
				alpha = 90 - rb_yaw;
				rotate_ang = (180 - 2*alpha) * (1);
			} 
			// robot at far wall
			else if (FR == 0 && FL == 1) {
				alpha = rb_yaw;
				rotate_ang = (180 - 2*alpha) * (-1);
			}

		// robot at far wall	
		} else if (rb_yaw >= -5 && rb_yaw < 5) {
			rotate_ang = -180;

		// robot facing far wall
		} else if (rb_yaw >= 5 && rb_yaw < 85) {
			// robot at far wall
			if (FR == 1 && FL == 0){
				alpha = rb_yaw;
				rotate_ang = (180 - 2*alpha) * (1);
			} 
			// robot at left wall
			else if (FR == 0 && FL == 1) {
				alpha = 90 - rb_yaw;
				rotate_ang = (180 - 2*alpha) * (-1);
			}
		// robot facing left wall
		} else if (rb_yaw >= 85 && rb_yaw < 95) {
			// turn towards the delivery wall
			if (rb_x >= 1.2){
				rotate_ang = 90;
			}else {
				rotate_ang = -90;
			}
		// robot facing delivery wall
		} else if (rb_yaw >= 95 && rb_yaw < 175) {
			// robot at left wall
			if (FR == 1 && FL == 0){
				alpha = rb_yaw - 90;
				rotate_ang = (180 - 2*alpha) * (1);
			} 
			// robot at delivery wall
			else if (FR == 0 && FL == 1) {
				alpha = 180 - rb_yaw;
				rotate_ang = (180 - 2*alpha) * (-1);
			}
		// robot facing delivery wall and at delivery wall
		} else if (rb_yaw > 175 && rb_yaw <= -175) {
			rotate_ang = -180;
		}

		edge_goal_yaw = rb_yaw + rotate_ang;
		return;
	}
	//status 2: only backward sensors detetcted
	else if((BL == 1 || BR == 1) && (FL != 1 && FR != 1)){
		edge_goal_yaw = 0.0;
		edge_linX_sign = 1;
		return;
	}
	//Some special cases: in corner
	else{
		edge_goal_yaw = rb_yaw;
		return;
	}
}

/// @brief Performs edge avoidance
/// @param rb_x robot's x position
/// @param rb_y robot's y position
/// @param rb_yaw robot's current yaw
/// @return the previous task if successful, EDGE otherwise
int edge_avoid_task(float rb_x, float rb_y, float rb_yaw, int prev_task){
	float distance_from_edge = calculate_distance(rb_x, rb_y, edge_x, edge_y);
	float yaw_error = edge_goal_yaw - rb_yaw;

	if (distance_from_edge > EDGE_REVERSE_DISTANCE && abs(yaw_error) < YAW_TOLERANCE){
		edge_linX = 0.0;
		edge_angZ = 0.0;
		return prev_task;
	}
	else if (distance_from_edge < EDGE_REVERSE_DISTANCE){
		edge_linX = edge_linX_sign * MAX_SPEED;
		edge_angZ = 0.0;
		return EDGE;
	}
	else if (fabs(yaw_error) > YAW_TOLERANCE){
		edge_linX = 0.0;
		edge_angZ = 0.6 * yaw_error;
		return EDGE;
	}
}

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