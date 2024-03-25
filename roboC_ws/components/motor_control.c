#include "../config.h"

/* _____________________________________________________________________________________________________________________

MOTORS CONTROL
_____________________________________________________________________________________________________________________ */

/**
 * @brief Open loop control of motor speed rpm
 * @param rpmR The right motor speed in rpm
 * @param rpmL The left motor speed in rpm
*/
void robot_move_open(float rpmR, float rpmL){
	motor[motor_R] = rpmR / MAX_WHEEL_RPM * 127;
	motor[motor_L] = rpmL / MAX_WHEEL_RPM * 127;
}

/**
 * @brief Closed loop control of motor speed rpm
 * @param en_rpmR The right motor speed in rpm
 * @param en_rpmL The left motor speed in rpm
 * @param cmd_rpmR The desired right motor speed in rpm
 * @param cmd_rpmL The desired left motor speed in rpm
*/
void robot_move_closed(float en_rpmR, float en_rpmL, float cmd_rpmR, float cmd_rpmL){
	int motor_power_R = pid_R(en_rpmR, cmd_rpmR);
	int motor_power_L = pid_L(en_rpmL, cmd_rpmL);
	motor_power_R = limit_byte(motor_power_R);
	motor_power_L = limit_byte(motor_power_L);
	motor[motor_R] = motor_power_R;
	motor[motor_L] = motor_power_L;
}

/**
 * @brief Open loop control of servo displacement
 * @param displacement The servo displacement
*/
void robot_servo_open(int displacement){
	int move_time_ms = displacement * SERVO_DISPLACEMNT_FACTOR;
	int servo_power = limit_byte(displacement * SERVO_POWER_FACTOR);
	while (time1[T2] < move_time_ms){
		motor[servo] = servo_power;
	}
	motor[servo] = 0;
}