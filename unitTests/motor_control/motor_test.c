#pragma config(Sensor, in1,    long_distance_R_pin, sensorAnalog)
#pragma config(Sensor, in2,    long_distance_M_pin, sensorAnalog)
#pragma config(Sensor, in3,    long_distance_L_pin, sensorAnalog)
#pragma config(Sensor, in4,    short_distance_T_pin, sensorAnalog)
#pragma config(Sensor, in5,    line_BR_pin,        sensorAnalog)
#pragma config(Sensor, in6,    line_FR_pin,        sensorAnalog)
#pragma config(Sensor, in7,    line_FL_pin,        sensorAnalog)
#pragma config(Sensor, in8,    line_BL_pin,        sensorAnalog)
#pragma config(Sensor, dgtl1,  wheel_L_encoderA_pin, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  wheel_R_encoderA_pin, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  limit_switch_A_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl6,  limit_switch_B_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl7,  limit_switch_C_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl8,  limit_switch_D_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl9,  magneto_north_pin,  sensorDigitalIn)
#pragma config(Sensor, dgtl10, magneto_south_pin,  sensorDigitalIn)
#pragma config(Sensor, dgtl11, magneto_east_pin,   sensorDigitalIn)
#pragma config(Sensor, dgtl12, magneto_west_pin,   sensorDigitalIn)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           motor_R,       tmotorVex393_MC29, PIDControl, encoderPort, dgtl3)
#pragma config(Motor,  port7,           motor_L,       tmotorVex393_MC29, PIDControl, reversed, encoderPort, dgtl1)

#include "motor_test.h"
#include "motor_control.c"
#include "servo_control.c"

/*
Note the following:
1. This file is used to TEST and CALIBRATE the motors of the drive system and the servo
2. The parameters to calibrate are located in motor_test.h and the following are to be calibrated
	- MOTOR_L_KP
	- MOTOR_L_KI
	- MOTOR_L_KD
	- MOTOR_R_KP
	- MOTOR_R_KI
	- MOTOR_R_KD
	- SERVO_ARM_TOLERANCE = the tolerance of the arm's position. it is used to determine if the servo motor should stop. 
	- SERVO_POSITION_GAIN = the estimated angle of displacement when the servo is activated in one cycle. i.e. in 0.05 [s] how much does the arm move
	- SWITCH_A_POSITION = the position of the limit switch A which is somewhere in the outward position
	- SWITCH_B_POSITION = the position of the limit switch B which is somewhere in the middle position
	- SWITCH_C_POSITION = the position of the limit switch C which is somewhere in the inward position
2. 	IMPORTANT!! The characteristic of the motor and the code sets up the KI value to be the most important. The higher the 
	value, the faster steady state speed is achieved but too high will cause oscillations. please observe the integral component the PID
3. Code found between the TEST_CODE_BEGIN and TEST_CODE_END are strictly for testing and not to be used in the final robot
*/

// TEST CODE BEGIN
float calc_linear_x(float rpmL, float rpmR){
	float linX = (rpmR + rpmL) / RADIAN_T0_RPM * WHEEL_DIAMETER /4;
	return linX;
}

float calc_angular_z(float rpmL, float rpmR){
	float angZ = (rpmR - rpmL) * WHEEL_DIAMETER/ROBOT_TRACK / RADIAN_T0_RPM / DEGREE_TO_RADIAN;
	return angZ;
}
// TEST CODE END

/* _____________________________________________________________________________________________________________________

SENSORS
_____________________________________________________________________________________________________________________ */

static int limit_switch_A;
static int limit_switch_B;
static int limit_switch_C;

static float robot_en_rpmR;
static float robot_en_rpmL;

// TESTING CODE BEGIN
static float robot_en_linX;
static float robot_en_angZ;
// TESTING CODE END

static float robot_arm_position;

/* _____________________________________________________________________________________________________________________

GLOBAL VARIABLES
_____________________________________________________________________________________________________________________ */

static float robot_cmd_linX;
static float robot_cmd_angZ;
static float robot_cmd_rpmL;
static float robot_cmd_rpmR;

static float robot_cmd_arm;

static int loop_ms;

// Updates all sensor values
void read_sensors(void){
    limit_switch_A = SensorValue[limit_switch_A_pin];
    limit_switch_B = SensorValue[limit_switch_B_pin];
    limit_switch_C = SensorValue[limit_switch_C_pin];

	robot_arm_position = get_arm_position(SensorValue[limit_switch_A_pin], SensorValue[limit_switch_B_pin], SensorValue[limit_switch_C_pin]);

	robot_en_rpmR = getMotorEncoder(motor_R) / ENCODER_RESOLUTION * 60.0/DT;
	robot_en_rpmL = getMotorEncoder(motor_L) / ENCODER_RESOLUTION * 60.0/DT;

	// TESTING CODE BEGIN
	robot_en_linX = calc_linear_x(robot_en_rpmR, robot_en_rpmR);
	robot_en_angZ = calc_angular_z(robot_en_rpmR, robot_en_rpmL);
	// TESTING CODE END

	set_motor_status(robot_en_rpmL, robot_en_rpmR);

	resetMotorEncoder(motor_R);
	resetMotorEncoder(motor_L);
}

void robot_execute(){
	robot_base_move(robot_cmd_linX, robot_cmd_angZ);
	robot_cmd_linX = get_cmd_linX();
	robot_cmd_angZ = get_cmd_angZ();
	robot_cmd_rpmL = get_cmd_rpmL();
	robot_cmd_rpmR = get_cmd_rpmR();

	robot_arm_move(robot_cmd_arm);
}
/**
 * @brief Initialises the robot
*/
void init(){
	int ready = 0;
	while (ready != 1){
		read_sensors();
		// Init arm
		if (robot_arm_position < 180.0){
			robot_arm_move(180.0);
		}
		else{
			robot_arm_move(0.0);
		}
		// Reset encoders
		resetMotorEncoder(motor_L);
		resetMotorEncoder(motor_R);
		// Ready criteria
		if (robot_arm_position < ARM_TOLERANCE){
			ready = 1;
			break;
		}
	}
}

// TEST CODE BEGIN
/**
 * @brief Simulates a robot task by floating point operations
 * @param n number of operations
*/
void floppy(int n){
	for (int i = 0; i < n; i++){
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
	return;
}

/** 
 * @brief Sets the motors to a constant speed and updates the commanded rpm and speeds based on limitations
 * @param linX desired linear velocity in M/S
 * @param angZ desired angular velocity in DEG/S
*/
void constant_speed(float linX, float angZ){
	robot_base_move(robot_cmd_linX, robot_cmd_angZ);
	robot_cmd_linX = get_cmd_linX();
	robot_cmd_angZ = get_cmd_angZ();
	robot_cmd_rpmL = get_cmd_rpmL();
	robot_cmd_rpmR = get_cmd_rpmR();
	return;
}

/**
 * @brief Sets the motors to a constant RPM and updates the commanded RPM based on limitations. This is only for TESTING
 * @param rpmL desired LEFT wheel rpm
 * @param rpmR desired RIGHT wheel rpm
*/
void constant_rpm(float rpmL, float rpmR){
	robot_move_rpm(rpmL, rpmR);
	robot_cmd_linX = NULL;
	robot_cmd_angZ = NULL;
	robot_cmd_rpmL = get_cmd_rpmL();
	robot_cmd_rpmR = get_cmd_rpmR();
	return;
}
// TEST CODE END

task main()
{
	init();
	while(1){
		read_sensors();
		// robot_execute(robot_cmd_linX, robot_cmd_angZ, robot_cmd_arm);
		clearTimer(T1);
		// Main Loop

		floppy(1000);

		/*________________________________________

		DRIVE MOTOR TESTING
		________________________________________*/		
		// constant_power(20, 0);
		constant_rpm(60, 60);
		// constant_speed(0.4, 0.4);

		/*________________________________________

		SERVO MOTOR TESTING
		________________________________________*/		

		// set a position
		robot_arm_move(0.0);
	

		while (time1[T1] < DT * 1000){}
		loop_ms = time1[T1];
	}
}
