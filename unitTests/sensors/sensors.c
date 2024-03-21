#pragma config(Sensor, in1,    long_distance_R, sensorAnalog)
#pragma config(Sensor, in2,    short_distance, sensorAnalog)
#pragma config(Sensor, in3,    long_distance_L, sensorAnalog)
#pragma config(Sensor, in4,    long_distance_top, sensorAnalog)
#pragma config(Sensor, in5,    line_BR,        sensorAnalog)
#pragma config(Sensor, in6,    line_FR,        sensorAnalog)
#pragma config(Sensor, in7,    line_FL,        sensorAnalog)
#pragma config(Sensor, in8,    line_BL,        sensorAnalog)
#pragma config(Sensor, dgtl2,  wheel_L_encoderA, sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  wheel_R_encoderA, sensorQuadEncoder)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           motor_R,       tmotorVex393_MC29, PIDControl, encoderPort, dgtl4)
#pragma config(Motor,  port7,           motor_L,       tmotorVex393_MC29, PIDControl, reversed, encoderPort, dgtl2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "sensors.h"
#include "filter.c"

// global variables
int line_FL_val;
int line_BL_val;
int line_BR_val;
int	line_FR_val;

int prev_line_FL_val;
int prev_line_BL_val;
int prev_line_BR_val;
int	prev_line_FR_val;

int dis_L_val;
int dis_R_val;
int dis_mid_val;
int dis_top_val;

int prev_dis_L_val;
int prev_dis_R_val;
int prev_dis_mid_val;
int prev_dis_top_val;

int d_enR;
int d_enL;
float m_rpmR;
float m_rpmL;

int loop_ms;


float read_long_sensor_distance_CM(float sensor_val){
  //convert voltage reading from long dist sensor into distance in cm
  float voltage = sensor_val * BYTE_TO_VOLT;
  
  //step-by-step calculation as arduino cannot handle PEMDAS
  float ln_voltage = log(voltage);
  float ln_voltage_square = ln_voltage*ln_voltage;
  float term_1 = 29.971*ln_voltage;
  float term_2 = 55.047*ln_voltage_square;
  float term_3 = 57.931*voltage;
  float distance_cm = term_1 + term_2 - term_3 + 84.019;
  return distance_cm;
}

float read_short_sensor_distance_CM(float sensor_val){
  //convert voltage reading from short dist sensor into distance in cm
  float voltage = sensor_val * BYTE_TO_VOLT;;
  
  //calculation for the short distance sensor here
  float exponent = -1/0.95;
  float base = voltage/11.033;
  float distance_cm = pow(base, exponent);
  return distance_cm;
}

int read_digitized_long_sensor_distance(float sensor_val){
  //read_long_sensor_distance_CM is a function that returns the distance (in cm) of the long range analog sensor reading
  if(read_long_sensor_distance_CM(sensor_val) <= LONG_DIST_LOWER_THRESHOLD_CM){
    return 1; //close range
  }
  else if(read_long_sensor_distance_CM(sensor_val) > LONG_DIST_UPPER_THRESHOLD_CM){
    return 0; //far, ignore detection
  }
  else{
    return 2; //detected in optimum range
  }
}

int read_digitized_short_sensor_distance(float sensor_val){
  //read_short_sensor_distance_CM is a function that returns the distance (in cm) of the long range analog sensor reading
  if(read_short_sensor_distance_CM(sensor_val) <= SHORT_DIST_THRESHOLD_CM){
    return 1; //detected
  }
  else{
    return 0; //no detection
  }
}

// sensors
/**
 * @brief Updates all sensor values
*/
void read_sensors(){
	prev_line_FL_val = line_FL_val;
	prev_line_BL_val = line_BL_val;
	prev_line_BR_val = line_BR_val;
	prev_line_FR_val = line_FR_val;
	line_FL_val = low_pass_filter(SensorValue[line_FL], prev_line_FL_val, CUTOFF_LINE_FL);
	line_BL_val = low_pass_filter(SensorValue[line_BL], prev_line_BL_val, CUTOFF_LINE_BL);
	line_BR_val = low_pass_filter(SensorValue[line_BR], prev_line_FL_val, CUTOFF_LINE_BR);
	line_FR_val = low_pass_filter(SensorValue[line_FR], prev_line_FL_val, CUTOFF_LINE_FR);

	prev_dis_L_val = dis_L_val;
	prev_dis_R_val = dis_R_val;
	prev_dis_mid_val = dis_mid_val;
	prev_dis_top_val = dis_top_val;
	dis_L_val = low_pass_filter(SensorValue[long_distance_L], prev_dis_L_val, CUTOFF_LONG_L);
	dis_R_val = low_pass_filter(SensorValue[long_distance_R], prev_dis_R_val, CUTOFF_LONG_R);
	dis_mid_val = low_pass_filter(SensorValue[short_distance], prev_dis_mid_val, CUTOFF_SHORT);
	dis_top_val = low_pass_filter(SensorValue[long_distance_top], prev_dis_top_val, CUTOFF_LONG_T);
	dis_mid_val = read_digitized_short_sensor_distance(dis_mid_val);
	dis_top_val = read_digitized_long_sensor_distance(dis_top_val);


	d_enR = getMotorEncoder(motor_R);
	d_enL = getMotorEncoder(motor_L);
	m_rpmR = d_enR * 60/DT /ENCODER_RESOLUTION;
  	m_rpmL = d_enL * 60/DT /ENCODER_RESOLUTION;

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
	for (unsigned int i = 0; i < n; i++){
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
