#pragma config(Sensor, in1,    long_distance_R, sensorAnalog)
#pragma config(Sensor, in2,    long_distance_M, sensorAnalog)
#pragma config(Sensor, in3,    long_distance_L, sensorAnalog)
#pragma config(Sensor, in4,    short_distance_T, sensorAnalog)
#pragma config(Sensor, in5,    line_BR,        sensorAnalog)
#pragma config(Sensor, in6,    line_FR,        sensorAnalog)
#pragma config(Sensor, in7,    line_FL,        sensorAnalog)
#pragma config(Sensor, in8,    line_BL,        sensorAnalog)
#pragma config(Sensor, dgtl1,  wheel_L_encoderA, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  wheel_R_encoderA, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  limit_switch_A_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl6,  limit_switch_B_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl7,  limit_switch_C_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl8,  limit_switch_D_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl9,  magneto_north,  sensorDigitalIn)
#pragma config(Sensor, dgtl10, magneto_south,  sensorDigitalIn)
#pragma config(Sensor, dgtl11, magneto_east,   sensorDigitalIn)
#pragma config(Sensor, dgtl12, magneto_west,   sensorDigitalIn)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           motor_R,       tmotorVex393_MC29, PIDControl, encoderPort, dgtl3)
#pragma config(Motor,  port7,           motor_L,       tmotorVex393_MC29, PIDControl, reversed, encoderPort, dgtl1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "support.c"
#include "sensors_test.h"
#include "sensors.c"

// global variables
static float line_FL_val;
static float line_BL_val;
static float line_BR_val;
static float line_FR_val;

static float distance_L;
static float distance_R;
static float distance_mid;
static float distance_top;

static float m_rpmR;
static float m_rpmL;

static int limit_switch_A;
static int limit_switch_B;
static int limit_switch_C;
static int limit_switch_D;

static float compass_yaw;

static int loop_ms; // ensure loop runs at 50ms

// sensors
/**
 * @brief Updates all sensor values
*/
void read_sensors(){
    compass_yaw = wrap_angle(read_compass(SensorValue[magneto_north], SensorValue[magneto_south], SensorValue[magneto_east], SensorValue[magneto_west]) - MAGNETOMETER_OFFSET);

    limit_switch_A = SensorValue[limit_switch_A_pin];
    limit_switch_B = SensorValue[limit_switch_B_pin];
    limit_switch_C = SensorValue[limit_switch_C_pin];
    limit_switch_D = SensorValue[limit_switch_D_pin];

	line_FL_val = filter_line_FL(SensorValue[line_FL]);
	line_BL_val = filter_line_BL(SensorValue[line_BL]);
	line_BR_val = filter_line_BR(SensorValue[line_BR]);
	line_FR_val = filter_line_FR(SensorValue[line_FR]);

	distance_mid = calculate_long_distance(filter_distance_mid(SensorValue[long_distance_M])) - MID_SENSOR_OFFSET;
	distance_top = calculate_short_distance(filter_distance_top(SensorValue[short_distance_T])) - TOP_SENSOR_OFFSET;
	distance_L = calculate_long_distance(filter_distance_L(SensorValue[long_distance_L])) - LEFT_SENSOR_OFFSET;
	distance_R = calculate_long_distance(filter_distance_R(SensorValue[long_distance_R])) - RIGHT_SENSOR_OFFSET;

    m_rpmL = getMotorEncoder(motor_L) * 60/DT /ENCODER_RESOLUTION;
	m_rpmR = getMotorEncoder(motor_R) * 60/DT /ENCODER_RESOLUTION;
	resetMotorEncoder(motor_R);
	resetMotorEncoder(motor_L);

}

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
	for (int i = 0; i < n; i++){
	float ans = 5.0 / 13.0;
	}
}

task main()
{
	init();
	while(1){
		clearTimer(T1);
		read_sensors();
		// Main Loop
		floppy(1000);

		while (time1[T1] < DT * 1000){}
		loop_ms = time1[T1];
	}
}