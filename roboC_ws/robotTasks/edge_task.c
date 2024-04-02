#include "../config.h"
#include "../components/motor_control.c"
#include "../components/controller.c"
#include "../components/motor.c"
#include "../components/sensors.c"

// @FANZIFU

static float edge_linX = 0.0;
static float edge_angZ = 0.0;

static float yaw;
static float rb_x;
static int FL;
static int FR;
static int BL;
static int BR;
float expected_yaw;
float alpha;
float rotate_ang;

int edge_detected(int FL, int BL, int BR, int FR){
	if (FL > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
	if (BL > LINE_BL_THRESHOLD){
		return 1;
		} else  {
		return 0;
	}
	if (BR > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
	if (FR > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
}

int avoid_case_check(float robot_x, float robot_yaw, int FL, int FR, int BL, int BR){
	FL = FL;
	FR = FR;
	BL = BL;
	BR = BR;
	rb_x = robot_x;
	yaw = robot_yaw;
	//status 1: forward sensor detetcted
	if ((FL == 1 || FR == 1) && (BL != 1 && BR != 1)){
		if (yaw >= -175 && yaw < -95) {
			if (FR == 1 && FL == 0){
				alpha = 180 - yaw;
				rotate_ang = (180 - 2*alpha) * (1);
			} 
			else if (FR == 0 && FL == 1) {
				alpha = yaw - 90;
				rotate_ang = (180 - 2*alpha) * (-1);
			}

		} else if (yaw >= -95 && yaw < -85) {

			if (rb_x >= 120){
				rotate_ang = -90;
			}else {
				rotate_ang = 90;
			}

		} else if (yaw >= -85 && yaw < -5) {
			if (FR == 1 && FL == 0){
				alpha = 90 - yaw;
				rotate_ang = (180 - 2*alpha) * (1);
			} 
			else if (FR == 0 && FL == 1) {
				alpha = yaw;
				rotate_ang = (180 - 2*alpha) * (-1);
			}
		} else if (yaw >= -5 && yaw < 5) {
			rotate_ang = -180;

		} else if (yaw >= 5 && yaw < 85) {
			if (FR == 1 && FL == 0){
				alpha = yaw;
				rotate_ang = (180 - 2*alpha) * (1);
			} 
			else if (FR == 0 && FL == 1) {
				alpha = 90 - yaw;
				rotate_ang = (180 - 2*alpha) * (-1);
			}
		} else if (yaw >= 85 && yaw < 95) {
			if (rb_x >= 120){
				rotate_ang = 90;
			}else {
				rotate_ang = -90;
			}
		} else if (yaw >= 95 && yaw < 175) {
			if (FR == 1 && FL == 0){
				alpha = yaw - 90;
				rotate_ang = (180 - 2*alpha) * (1);
			} 
			else if (FR == 0 && FL == 1) {
				alpha = 180 - yaw;
				rotate_ang = (180 - 2*alpha) * (-1);
			}
		} else if (yaw > 175 && yaw <= -175) {
			rotate_ang = -180;
		}
		expected_yaw = yaw + rotate_ang;
		return 1;
	}
	//status 2: backward sensor detetcted
	else if((BL == 1 || BR == 1) && (FL != 1 && FR != 1)){

		return 2;
	}
	//Some special cases: in corner
	else{
		// In corner always rotate +-90. rotate angle should be +-90
		rotate_ang = ;
		expected_yaw = yaw + rotate_ang;
		return 3;
	}
}



void edge_avoid_F(float yaw){

	yaw = yaw;
	float set_linX;
    float set_angZ;
	static int success = 0;

	if (fabs(yaw-expected_yaw) < YAW_THRESHOLD){
		success = 1;
		return 0;
	}
	
	// linX will always be 0, since rotate only
	set_linX = 0;
	set_angZ = MAX_TURN;

	if (abs(yaw - expected_yaw) > YAW_THRESHOLD) {
		if (rotate_ang >= 0){
			robot_move(set_linX, set_angZ);
		} else {
			robot_move(set_linX, -set_angZ);
		}
	}
	robot_move(0,0);
	if (success == 1){
		return 0;//which means avoid status == 0
	}
	else {
		return 1;
	}
}

void edge_avoid_B(){
	//only BR, BL are detected, just move forward
	static int success = 0;
	robot_move(MAX_SPEED,0);
	sleep(500); //let the robot move in MAX_SPEED for 500ms
	robot_move(0,0);
	return 2;
}

void edge_avoid_S(float yaw){

	yaw = yaw;
	float set_linX;
    float set_angZ;
	static int success = 0;

	if (fabs(yaw-expected_yaw) < YAW_THRESHOLD){
		success = 1;
		return 0;
	}
	
	// linX will always be 0, since rotate only
	set_linX = 0;
	set_angZ = MAX_TURN;

	if (abs(yaw - expected_yaw) > YAW_THRESHOLD) {
		if (rotate_ang >= 0){
			robot_move(set_linX, set_angZ);
		} else {
			robot_move(set_linX, -set_angZ);
		}
	}
	robot_move(0,0);
	if (success == 1){
		return 0;//which means avoid status == 0
	}
	else {
		return 3;
	}
}