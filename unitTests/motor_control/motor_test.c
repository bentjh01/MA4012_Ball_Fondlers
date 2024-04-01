
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


/* _____________________________________________________________________________________________________________________

SENSORS
_____________________________________________________________________________________________________________________ */

static int limit_switch_A;
static int limit_switch_B;
static int limit_switch_C;

static float robot_en_rpmR;
static float robot_en_rpmL;

static float robot_en_linX;
static float robot_en_angZ;

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
static int main_dt;

// Updates all sensor values
void read_sensors(void){
	robot_arm_position = get_arm_position(limit_switch_A, limit_switch_B, limit_switch_C);

	robot_en_rpmR = getMotorEncoder(motor_R) / ENCODER_RESOLUTION * 60.0/DT;
	robot_en_rpmL = getMotorEncoder(motor_L) / ENCODER_RESOLUTION * 60.0/DT;

	robot_en_linX = calculate_linear_x(robot_en_rpmR, robot_en_rpmR);
	robot_en_angZ = calculate_angular_z(robot_en_rpmR, robot_en_rpmL);

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

/* _____________________________________________________________________________________________________________________

TEST SCRIPT
_____________________________________________________________________________________________________________________ */

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
static float robot_cmd_rpmR;
static float robot_cmd_rpmL;
void constant_rpm(float rpmR, float rpmL){
	robot_cmd_rpmR = rpmR;
	robot_cmd_rpmL = rpmL;
	robot_cmd_rpmR = limit_rpmR(robot_cmd_rpmR, robot_cmd_rpmL);
	robot_cmd_rpmL = limit_rpmL(robot_cmd_rpmR, robot_cmd_rpmL);
	robot_move_closed(robot_cmd_rpmR, robot_cmd_rpmL);
}

task main()
{
	init();
	while(1){
		read_sensors();
		robot_execute(robot_cmd_linX, robot_cmd_angZ, robot_cmd_arm);
		clearTimer(T1);
		// Main Loop

		floppy(1000);

		// constant_power(20, 0);

		robot_cmd_linX = 0.2;
		robot_cmd_angZ = 0.0;

		while (time1[T1] < DT * 1000){}
		loop_ms = time1[T1];
	}
}
