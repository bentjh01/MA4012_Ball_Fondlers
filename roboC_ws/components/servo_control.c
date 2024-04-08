#include "../config.h"

/**
 * @brief Updates the value of the arm position.
 * @param
 * @param switch_A digital reading of limit switch A
 * @param switch_B digital reading of limit switch B
 * @param switch_C digital reading of limit switch C
 * @return updated arm position in DEG
*/
float get_arm_position(float arm_position, float set_cmd, float servo_direction, int switch_A, int switch_B, int switch_C){
    static float prev_switch;
    if (switch_A == TRIGGERED){
        prev_switch = SWITCH_A_POSITION;
        return SWITCH_A_POSITION;
    }
    else if (switch_B == TRIGGERED){
        prev_switch = SWITCH_B_POSITION;
        return SWITCH_B_POSITION;
    }
    else if (switch_C == TRIGGERED){
        prev_switch = SWITCH_C_POSITION;
        return SWITCH_C_POSITION;
    }
    else if (prev_switch == SWITCH_A_POSITION && switch_B != TRIGGERED){
        return (SWITCH_A_POSITION + SWITCH_B_POSITION)/2.0;
    }
    else if (prev_switch == SWITCH_C_POSITION && switch_B != TRIGGERED){
        return (SWITCH_C_POSITION + SWITCH_B_POSITION)/2.0;
    }
    else if (prev_switch == SWITCH_B_POSITION && servo_direction > 0){
        prev_switch = SWITCH_C_POSITION;
        return (SWITCH_C_POSITION + SWITCH_B_POSITION)/2.0;
    }
    else if (prev_switch == SWITCH_B_POSITION && servo_direction < 0){
        prev_switch = SWITCH_A_POSITION;
       return (SWITCH_A_POSITION + SWITCH_B_POSITION)/2.0;
    }
    else{
        return arm_position;
    }

    if (switch_A == TRIGGERED){
        return SWITCH_A_POSITION;
    }
    else if (switch_B == TRIGGERED){
        return SWITCH_B_POSITION;
    }
    else if (switch_C == TRIGGERED){
        return SWITCH_C_POSITION;
    }
    // else if (fabs(set_cmd - arm_position) > SERVO_TOLERANCE){
    //     return arm_position + servo_direction * SERVO_POSITION_GAIN;
    // }
    else{
        return arm_position;
    }
}

/**
 * @brief Sets the desired position of the servo and actuates if it is not there
 * @param set_position desired position of the servo in DEG
 * @return direction of the arm
*/
float robot_arm_move(float set_position, float arm_position){
    static float prev_direction;
    float err_arm = set_position - arm_position;
    float set_servo_power = 0;
    // position of arm is -1 at most open, and 180 at most closed
    // when motor is set to positive, arm swings inwards
	if (fabs(err_arm) > SERVO_TOLERANCE){
		// set_servo_power = sgn(err_arm) * MAX_POWER * SERVO_GAIN;
		set_servo_power = err_arm * SERVO_KP;
    set_servo_power = limit_byte(set_servo_power);
	}
    motor[servo] = -set_servo_power;
    if (sgn(err_arm) == 0){
        return prev_direction;
    }
    prev_direction = sgn(err_arm);
    return sgn(err_arm);
}
