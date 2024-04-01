#include "../config.h"
#include "../components/motor_control.c"
#include "../components/controller.c"
#include "../components/motor.c"
#include "../components/sensors.c"

// @FANZIFU

int edge_detected(int FL, int BL, int BR, int FR){
	if (FL > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
	if (BL > LINE_BL_THRESHOLD){
		return 1;
		} else {
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

static float rb_yaw;
static float rb_x;
static int FL;
static int FR;


void edge_avoid(float robot_x, float yaw, int FL, int FR){

	rb_yaw = yaw;
    rb_x = robot_x;
	FL = FL;
	FR = FR;

	static float alpha;
    static float rotate_ang;
	float set_linX;
    float set_angZ;
	float current_yaw;
	float expected_yaw;

    // stop the motor first
	robot_move(0,0);
	
    if (yaw >= -175 && yaw < -95) {
		if (FR == 1 && FL == 0){
			alpha = 180 - rb_yaw;
		    rotate_ang = (180 - 2*alpha) * (1);
		} 
		else if (FR == 0 && FL == 1) {
			alpha = rb_yaw - 90;
		    rotate_ang = (180 - 2*alpha) * (-1);
		} else {
			// invalid case
			rotate_ang = 45;
		}

    } else if (yaw >= -95 && yaw < -85) {

        if (rb_x >= 120){
		    rotate_ang = -90;
		}else {
			rotate_ang = 90;
		}

    } else if (yaw >= -85 && yaw < -5) {
        if (FR == 1 && FL == 0){
			alpha = 90 - rb_yaw;
		    rotate_ang = (180 - 2*alpha) * (1);
		} 
		else if (FR == 0 && FL == 1) {
			alpha = rb_yaw;
		    rotate_ang = (180 - 2*alpha) * (-1);
		} else {
			// invalid case
			rotate_ang = 45;
		}
    } else if (yaw >= -5 && yaw < 5) {
        rotate_ang = -180;
    } else if (yaw >= 5 && yaw < 85) {
        if (FR == 1 && FL == 0){
			alpha = rb_yaw;
		    rotate_ang = (180 - 2*alpha) * (1);
		} 
		else if (FR == 0 && FL == 1) {
			alpha = 90 - rb_yaw;
		    rotate_ang = (180 - 2*alpha) * (-1);
		} else {
			// invalid case
			rotate_ang = 45;
		}
    } else if (yaw >= 85 && yaw < 95) {
        if (rb_x >= 120){
		    rotate_ang = 90;
		}else {
			rotate_ang = -90;
		}
    } else if (yaw >= 95 && yaw < 175) {
        if (FR == 1 && FL == 0){
			alpha = rb_yaw - 90;
		    rotate_ang = (180 - 2*alpha) * (1);
		} 
		else if (FR == 0 && FL == 1) {
			alpha = 180 - rb_yaw;
		    rotate_ang = (180 - 2*alpha) * (-1);
		} else {
			// invalid case
			rotate_ang = 45;
		}
    } else if (yaw >= 175 && yaw <= -175) {
        rotate_ang = -180;
    }
	// linX will always be 0, since rotate only
	set_linX = 0;

	set_angZ = MAX_TURN;

	// update current yaw value into variable current_yaw
	current_yaw = yaw;
	expected_yaw = rb_yaw + rotate_ang;

	while (abs(current_yaw - expected_yaw) > YAW_THRESHOLD) {
		if (rotate_ang >= 0){
			robot_move(set_linX, set_angZ);
		} else {
			robot_move(set_linX, -set_angZ);
		}
	}
	robot_move(0,0);
}