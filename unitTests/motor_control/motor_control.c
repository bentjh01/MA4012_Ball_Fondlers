#include "motor_test.h"
#include "controller.c"

/* _____________________________________________________________________________________________________________________

MOTORS CONTROL
_____________________________________________________________________________________________________________________ */

static float motor_en_rpmL;
static float motor_en_rpmR;

static float motor_rpmL;
static float motor_rpmR;
static float motor_linX;
static float motor_angZ;

/**
 * @brief Updates the values of the encoder readings for closed lop control
 * @param rpmL current LEFT motor RPM
 * @param rpmR current RIGHT motor RPM
*/
void set_motor_status(float rpmL, float rpmR){
	motor_en_rpmL = rpmL;
	motor_en_rpmR = rpmR;
}

/**
 * @brief Open loop control of motor speed rpm
 * @param rpmL The right motor speed in rpm
 * @param rpmR The left motor speed in rpm
*/
void robot_move_open(float rpmL, float rpmR){
	motor[motor_R] = rpm_to_power(rpmR);
	motor[motor_L] = rpm_to_power(rpmL);
}

/**
 * @brief Closed loop control of motor speed rpm
 * @param cmd_rpmR The desired RIGHT motor speed in RPM
 * @param cmd_rpmL The desired LEFT motor speed in RPM
*/
void robot_move_closed(float cmd_rpmL, float cmd_rpmR, float en_rpmL, float en_rpmR){
	int motor_power_R = pid_R(cmd_rpmR, en_rpmR);
	int motor_power_L = pid_L(cmd_rpmL, en_rpmL);
	motor_power_R = limit_byte(motor_power_R);
	motor_power_L = limit_byte(motor_power_L);
	motor[motor_R] = motor_power_R;
	motor[motor_L] = motor_power_L;
}

/**
 * @brief Executes motors on base of robot to move
 * @param linear_x desired linear velocity in M/S
 * @param angular_z desired angular velocity in DEG/S
*/
void robot_base_move(float linear_x, float angular_z){
	motor_rpmL = calcualte_rpmL(linear_x, angular_z);
	motor_rpmR = calcualte_rpmR(linear_x, angular_z);
	motor_rpmL = limit_rpmL(motor_rpmL, motor_rpmR);
	motor_rpmR = limit_rpmR(motor_rpmL, motor_rpmR);
	motor_linX = calculate_linear_x(motor_rpmL, motor_rpmR);
	motor_angZ = calculate_angular_z(motor_rpmL, motor_rpmR);
	robot_move_closed(motor_rpmL, motor_rpmR, motor_en_rpmL, motor_en_rpmR);
}

float get_cmd_rpmL(){
	return motor_rpmL;
}

float get_cmd_rpmR(){
	return motor_rpmR;
}

float get_cmd_linX(){
	return motor_linX;
}

float get_cmd_angZ(){
	return motor_angZ;
}