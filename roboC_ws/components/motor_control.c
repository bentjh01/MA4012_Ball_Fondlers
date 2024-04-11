#include "config.h"

#include "controller.c"
#include "motor.c"
#include "differential_drive.c"

/* _____________________________________________________________________________________________________________________

MOTORS CONTROL
_____________________________________________________________________________________________________________________ */

// RPM to POWER conversion
float rpmL_to_powerL(float rpm){
	if (rpm == 0.0){
		return 0.0;
	}
	return sgn(rpm)*(14.893*pow(E,0.0126*fabs(rpm)));
}
float rpmR_to_powerR(float rpm){
	if (rpm ==0.0){
		return 0.0;
	}
	return sgn(rpm)*(13.782 * pow(E,0.0128*fabs(rpm)));
}

/**
 * @brief Open loop control of motor speed rpm
 * @param rpmL The right motor speed in rpm
 * @param rpmR The left motor speed in rpm
*/
void robot_move_open(float rpmL, float rpmR){
	motor[motor_L] = rpmL_to_powerL(rpmL);
	motor[motor_R] = rpmR_to_powerR(rpmR);
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
void robot_move_closed(float cmd_rpmL, float cmd_rpmR, float en_rpmL, float en_rpmR){
	float biasL = rpmL_to_powerL(cmd_rpmL);
	float biasR = rpmR_to_powerR(cmd_rpmR);
	int motor_power_L = pid_L(cmd_rpmL, en_rpmL, biasL);
	int motor_power_R = pid_R(cmd_rpmR, en_rpmR, biasR);
	motor[motor_L] = motor_power_L;
	motor[motor_R] = motor_power_R;
	return;
}
