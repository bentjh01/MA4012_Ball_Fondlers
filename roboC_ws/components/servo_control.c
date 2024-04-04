#include "../config.h"

/**
 * @brief Updates the value of the arm position. 
 * @param switch_A digital reading of limit switch A
 * @param switch_B digital reading of limit switch B
 * @param switch_C digital reading of limit switch C
 * @return updated arm position in DEG
*/
float get_arm_position(float arm_position, float servo_direction, int switch_A, int switch_B, int switch_C){
    if (switch_A == TRIGGERED){
        return SWITCH_A_POSITION;
    }
    else if (switch_B == TRIGGERED){
        return SWITCH_B_POSITION;
    }
    else if (switch_C == TRIGGERED){
        return SWITCH_C_POSITION;
    }
    else{
        return arm_position + (sgn(servo_direction) * SERVO_POSITION_GAIN);
    }
}

/**
 * @brief Sets the desired position of the servo and actuates if it is not there
 * @param set_position desired position of the servo in DEG
 * @return direction of the arm
*/
float robot_arm_move(float set_position, float arm_position){
    int set_servo_power = 0;
    // position of arm is -1 at most open, and 180 at most closed
    // when motor is set to positive, arm swings inwards
	if (fabs(set_position - arm_position) > SERVO_TOLERANCE){
		int set_servo_power = sgn(set_position - arm_position) * MAX_POWER;
	}
    motor[servo] = set_servo_power;
    return sgn(set_position - arm_position);
}