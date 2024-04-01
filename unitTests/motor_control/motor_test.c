#pragma config(Sensor, dgtl1,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  ,               sensorQuadEncoder)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           motor_R,       tmotorVex393_MC29, openLoop, encoderPort, dgtl3)
#pragma config(Motor,  port7,           motor_L,       tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "motor_test.h"
#include "motor.c"
#include "controller.c"
#include "motor_control.c"


/* _____________________________________________________________________________________________________________________

SENSORS
_____________________________________________________________________________________________________________________ */

static int robot_d_enR;
static int robot_d_enL;

static float robot_en_rpmR;
static float robot_en_rpmL;

static float robot_en_linX;
static float robot_en_angZ;

static float robot_cmd_linX;
static float robot_cmd_angZ;
static float robot_cmd_rpmR;
static float robot_cmd_rpmL;

static int loop_ms;
static int main_dt;

// executes velocity control
void robot_move(float linear_x, float angular_z){
	robot_en_rpmR = calcualte_rpmR(linear_x, angular_z);
	robot_en_rpmL = calcualte_rpmL(linear_x, angular_z);
	robot_en_rpmR = limit_rpmR(robot_cmd_rpmR, robot_cmd_rpmL);
	robot_en_rpmL = limit_rpmL(robot_cmd_rpmR, robot_cmd_rpmL);
	robot_cmd_linX = calculate_linear_x(robot_cmd_rpmR, robot_cmd_rpmL);
	robot_cmd_angZ = calculate_angular_z(robot_cmd_rpmR, robot_cmd_rpmL);
	robot_move_closed(robot_cmd_rpmR, robot_cmd_rpmL);
}

// Updates all sensor values
void read_sensors(void){

	robot_d_enR = getMotorEncoder(motor_R);
	robot_d_enL = getMotorEncoder(motor_L);

	// robot_en_rpmR = robot_d_enR / ENCODER_RESOLUTION * 60/DT;
  	// robot_en_rpmL = robot_d_enL / ENCODER_RESOLUTION * 60/DT;
	main_dt = (float)time1[T1]/1000.0;
	robot_en_rpmR = robot_d_enR / ENCODER_RESOLUTION * 60.0/DT;
	robot_en_rpmL = robot_d_enL / ENCODER_RESOLUTION * 60.0/DT;

	robot_en_linX = calculate_linear_x(robot_en_rpmR, robot_d_enL);
	robot_en_angZ = calculate_angular_z(robot_en_rpmR, robot_d_enL);

	update_controller_readings(robot_en_rpmR, robot_en_rpmL, DT);

	resetMotorEncoder(motor_R);
	resetMotorEncoder(motor_L);

	motor_execute(linX, angZ)
}

/* _____________________________________________________________________________________________________________________

TEST SCRIPT
_____________________________________________________________________________________________________________________ */

/**
 * @brief Initialises the robot
*/
void init(){
	resetMotorEncoder(motor_R);
	resetMotorEncoder(motor_L);
}

/**
 * @brief Simulates a robot task by floating point operations
 * @param n number of operations
*/
void floppy(int n){
	for (unsigned int i = 0; i < n; i++){
	float ans = 5.0 / 13.0;
	}
}

/**
 * @brief Sets the motor to a constant power
 * @param motor_power_R The right motor power -127 to 127
 * @param motor_power_L The left motor power -127 to 127
*/
void constant_power(int motor_power_R, int motor_power_L){
	motor[motor_R] = motor_power_R;
	motor[motor_L] = motor_power_L;
}

/**
 * @brief Sets the motor to a capped constant rpm in a closed loop
 * @param rpmR The right motor rpm
 * @param rpmL The left motor rpm
*/
void constant_rpm(float rpmR, float rpmL){
	robot_cmd_rpmR = rpmR;
	robot_cmd_rpmL = rpmL;
	robot_cmd_rpmR = limit_rpmR(robot_cmd_rpmR, robot_cmd_rpmL);
	robot_cmd_rpmL = limit_rpmL(robot_cmd_rpmR, robot_cmd_rpmL);
	robot_move_closed(robot_cmd_rpmR, robot_cmd_rpmL);
}

// returns the linear velocity
float roboTask_linX(){
	return 0.0;
}

// returns the angular velocity
float roboTask_angZ(){
	return 0.0;
}

task main()
{
	init();
	while(1){
		read_sensors();
		clearTimer(T1);
		// Main Loop

		floppy(1000);

		// constant_power(20, 0);
		constant_velocity(0.1, 0.0);
		// constant_rpm(60, 60);
		robot_cmd_linX = roboTask_linX();
		robot_cmd_angZ = roboTask_angZ();

		while (time1[T1] < DT * 1000){}
		loop_ms = time1[T1];
	}
}
