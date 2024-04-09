#include "config.h"

#include "controller.c"
#include "motor.c"
#include "differential_drive.c"

/* _____________________________________________________________________________________________________________________

MOTORS CONTROL
_____________________________________________________________________________________________________________________ */

// RPM to POWER conversion
float rpm_to_power(float rpm){
    if (rpm == 0) return 0;
    return sgn(rpm) * RPM_GAIN * pow(E, EXPONENT_GAIN * fabs(rpm));
}

/**
 * @brief Open loop control of motor speed rpm
 * @param rpmL The right motor speed in rpm
 * @param rpmR The left motor speed in rpm
*/
void robot_move_open(float rpmL, float rpmR){
	if (rpmL == INVALID || rpmR == INVALID){
		return;
	}
	motor[motor_R] = rpm_to_power(rpmR);
	motor[motor_L] = rpm_to_power(rpmL);
	return;
}

/**
 * @brief Moves the robot by controlling the motors.
 * @param cmd_rpmL The desired RPM (Rotations Per Minute) for the left motor.
 * @param cmd_rpmR The desired RPM (Rotations Per Minute) for the right motor.
 * @param en_rpmL The actual RPM (Rotations Per Minute) of the left motor.
 * @param en_rpmR The actual RPM (Rotations Per Minute) of the right motor.
 * @param dt The time interval between each call to the function.
 */
void robot_move_closed(float cmd_rpmL, float cmd_rpmR, float en_rpmL, float en_rpmR, float dt){
	if (cmd_rpmL == INVALID || cmd_rpmR == INVALID || en_rpmL == INVALID || en_rpmR == INVALID){
		return;
	}

	float biasL = rpm_to_power(cmd_rpmL);
	float biasR = rpm_to_power(cmd_rpmR);
	int motor_power_L = pid_L(cmd_rpmL, en_rpmL, biasL, dt);
	int motor_power_R = pid_R(cmd_rpmR, en_rpmR, biasR, dt);
	motor_power_L = limit_byteL(motor_power_L, motor_power_R);
	motor_power_R = limit_byteR(motor_power_L, motor_power_R);
	motor[motor_L] = motor_power_L;
	motor[motor_R] = motor_power_R;
	return;
}