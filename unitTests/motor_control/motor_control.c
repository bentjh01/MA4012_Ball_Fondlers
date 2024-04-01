#include "motor_test.h"

/* _____________________________________________________________________________________________________________________

MOTORS CONTROL
_____________________________________________________________________________________________________________________ */

/**
 * @brief Open loop control of motor speed rpm
 * @param rpmR The right motor speed in rpm
 * @param rpmL The left motor speed in rpm
*/
void robot_move_open(float rpmR, float rpmL){
	motor[motor_R] = power_rpm(rpmR);
	motor[motor_L] = power_rpm(rpmL);
}

/**
 * @brief Closed loop control of motor speed rpm
 * @param cmd_rpmR The desired right motor speed in rpm
 * @param cmd_rpmL The desired left motor speed in rpm
*/
void robot_move_closed(float cmd_rpmR, float cmd_rpmL){
	int motor_power_R = pid_R(cmd_rpmR);
	int motor_power_L = pid_L(cmd_rpmL);
	motor_power_R = limit_byte(motor_power_R);
	motor_power_L = limit_byte(motor_power_L);
	motor[motor_R] = motor_power_R;
	motor[motor_L] = motor_power_L;
}

/**
 * @brief Open loop control of servo displacement
 * @param displacement The servo displacement
*/
void robot_servo_open(int postion){
	int move_time_ms = angle * SERVO_DISPLACEMNT_FACTOR;
	// int servo_power = limit_byte(angle * SERVO_POWER_FACTOR);
	if (time1[T2] < move_time_ms){
		motor[servo] = 127;
	}
	else{
		motor[servo] = 0;
	}
}