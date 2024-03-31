#ifndef MOTOR_CONTROL_C
#define MOTOR_CONTROL_C

#include "../config.h"
#include "motor.c"
#include "controller.c"

/* _____________________________________________________________________________________________________________________

MOTORS CONTROL
_____________________________________________________________________________________________________________________ */

/**
 * @brief Open loop control of motor speed rpm
 * @param rpmR The right motor speed in rpm
 * @param rpmL The left motor speed in rpm
*/
void robot_move_open_rpm(float rpmR, float rpmL){
	motor[motor_R] = rpmR / MAX_WHEEL_RPM * 127;
	motor[motor_L] = rpmL / MAX_WHEEL_RPM * 127;
}

/**
 * @brief Open loop control of motor speed rpm
 * @param rpmR The right motor speed in rpm
 * @param rpmL The left motor speed in rpm
*/
void robot_move_open(float linear_x, float angular_z){
	float rpmR = calcualte_rpmR(linear_x, angular_z);
	float rpmL = calcualte_rpmL(linear_x, angular_z);
	rpmR = limit_rpmR(rpmR, rpmL);
	rpmL = limit_rpmL(rpmR, rpmL);
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
void robot_move_closed_rpm(float en_rpmR, float en_rpmL, float cmd_rpmR, float cmd_rpmL){
	int motor_power_R = pid_R(en_rpmR, cmd_rpmR);
	int motor_power_L = pid_L(en_rpmL, cmd_rpmL);
	motor_power_R = limit_byte(motor_power_R);
	motor_power_L = limit_byte(motor_power_L);
	motor[motor_R] = motor_power_R;
	motor[motor_L] = motor_power_L;
}

/**
 * @brief Closed loop control of robot movement
 * @param en_rpmR The right motor speed in rpm
 * @param en_rpmL The left motor speed in rpm
 * @param linear_X The linear velocity of the robot
 * @param angular_Z The angular velocity of the robot
*/
void robot_move_closed(float en_rpmR, float en_rpmL, float linear_X, float angular_Z){
	float cmd_rpmR = calcualte_rpmR(linear_X, angular_Z);
	float cmd_rpmL = calcualte_rpmL(linear_X, angular_Z);
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
// TODO- Encorporate Limit switch to know servo rough position. @Unizz20
void robot_servo_move(int displacement){
	int move_time_ms = displacement * SERVO_DISPLACEMNT_FACTOR;
	int servo_power = limit_byte(displacement * SERVO_POWER_FACTOR);
	while (time1[T2] < move_time_ms){
		motor[servo] = servo_power;
	}
	motor[servo] = 0;
}

#endif //MOTOR_CONTROL_C