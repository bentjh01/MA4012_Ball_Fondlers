#include "sensors.h"

//DEFINE PINS

int line_sensor_FL;
int line_sensor_BL;
int line_sensor_BR;
int line_sensor_FR;

float long_distance_sensor_FL;
float long_distance_sensor_FR;
float long_distance_sensor_TP;
float short_distance_sensor;

int limit_switch_chamber;
int limit_switch_BL;
int limit_switch_BR;

void init_sensors(void);
void read_compass(void);
void read_line_sensors(void);
void read_distance_sensors(void);
void read_limit_switches(void);


void init_sensors(void){

	// IR Line Tracking Sensor
	// FL = Front Left, BL = Back Right, etc.
  #pragma config(Sensor, in5,    line_BR,        sensorAnalog)
  #pragma config(Sensor, in6,    line_FR,        sensorAnalog)
  #pragma config(Sensor, in7,    line_FL,        sensorAnalog)
  #pragma config(Sensor, in8,    line_BL,        sensorAnalog)

  // Long Distance Sensor
  #pragma config(Sensor, in1,    long_distance_R, sensorAnalog)
  #pragma config(Sensor, in2,    long_distance_M, sensorAnalog)
  #pragma config(Sensor, in3,    long_distance_L, sensorAnalog)

  // Short Distance Sensor
  #pragma config(Sensor, in4,    short_distance_T, sensorAnalog)

  // Limit Switches
  #pragma config(Sensor, LIMIT_SWITCH_CHAMBER_PIN, limit_switch_chamber, sensorTouch)
  #pragma config(Sensor, LIMIT_SWITCH_BL_PIN,  limit_switch_BL,   sensorTouch)
  #pragma config(Sensor, LIMIT_SWITCH_BR_PIN,  limit_switch_BR,   sensorTouch)

  // Magnetometer
  #pragma config(Sensor, MAGNETOMETER_NORTH_PIN,  magnetometer_north, sensorTouch)
  #pragma config(Sensor, MAGNETOMETER_WEST_PIN,  magnetometer_west, sensorTouch)
  #pragma config(Sensor, MAGNETOMETER_SOUTH_PIN,  magnetometer_south, sensorTouch)
  #pragma config(Sensor, MAGNETOMETER_EAST_PIN,  magnetometer_east, sensorTouch)

}

void read_all_sensors(){
  read_line_sensors();
  read_distance_sensors();
  read_limit_switches();
  read_compass();
}

void read_distance_sensors(void){
  prev_long_distance_sensor_FL = long_distance_sensor_FL;
	prev_long_distance_sensor_FR = long_distance_sensor_FR;
	prev_short_distance_sensor = short_distance_sensor;
	prev_long_distance_sensor_MID = long_distance_sensor_MID;
	long_distance_sensor_FL = low_pass_filter(SensorValue[long_distance_L], prev_long_distance_sensor_FL, CUTOFF_LONG_L);
	long_distance_sensor_FR = low_pass_filter(SensorValue[long_distance_R], prev_long_distance_sensor_FR, CUTOFF_LONG_R);
	long_distance_sensor_MID = low_pass_filter(SensorValue[long_distance_M], prev_long_distance_sensor_MID, CUTOFF_LONG_T);
	short_distance_sensor = low_pass_filter(SensorValue[short_distance_T], prev_short_distance_sensor, CUTOFF_SHORT);
  
  return	long_distance_sensor_FL, long_distance_sensor_FR, long_distance_sensor_MID, short_distance_sensor

}

float read_long_sensor_distance_CM(float sensor_val){
  //convert voltage reading from long dist sensor into distance in cm
  float voltage = sensor_val / 1000.0; //convert from mV to V

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
  float voltage = sensor_val / 1000.0; //convert from mV to V

  //calculation for the short distance sensor here
  float exponent = -1/0.95;
  float base = voltage/11.033;
  float distance_cm = pow(base, exponent);
  return distance_cm;
}

int read_discretize_long_sensor_distance(float sensor_val){
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

int read_discretize_short_sensor_distance(float sensor_val){
  //read_short_sensor_distance_CM is a function that returns the distance (in cm) of the long range analog sensor reading
  if(read_short_sensor_distance_CM(sensor_val) <= SHORT_DIST_LOWER_THRESHOLD_CM){
    return 1; //detected
  }
  else if(read_short_sensor_distance_CM(sensor_val) >= SHORT_DIST_UPPER_THRESHOLD_CM){
    return 0; //no detection
  }
  else{
    return 2; //detected further away
  }
}

void read_limit_switches(void){
  limit_switch_chamber = digitalRead(limit_switch_chamber_PIN);
  limit_switch_BL = digitalRead(limit_switch_BL_PIN);
  limit_switch_BR = digitalRead(limit_switch_BR_PIN);
}

void read_compass(void){
  // int PIN1 = digitalRead(magnetometer_PIN1);
  // int PIN2 = digitalRead(magnetometer_PIN2);
  // int PIN3 = digitalRead(magnetometer_PIN3);
  // int PIN4 = digitalRead(magnetometer_PIN4);
  // NEED TO CHANGE TO VEX!

  int combination = PIN1 << 3 + PIN2 << 2 + PIN3 << 1 + PIN4;
  switch (combination)
  {
  case 0b1101:
    compass_bearing = NORTH;
    break;
  case 0b1001:
    compass_bearing = NORTH_EAST;
    break;
  case 0b1011:
    compass_bearing = EAST;
    break;
  case 0b0011:
    compass_bearing = SOUTH_EAST;
    break;
  case 0b0111:
    compass_bearing = SOUTH;
    break;
  case 0b0110:
    compass_bearing = SOUTH_WEST;
    break;
  case 0b1110:
    compass_bearing = WEST;
    break;
  case 0b1100:
    compass_bearing = NORTH_WEST;
    break;
  default:
    compass_bearing = NULL;
    break;
  }
}

void read_line_sensors(void){
  // line_sensor_FL = analogRead(line_sensor_FL_PIN);
  // line_sensor_BL = analogRead(line_sensor_BL_PIN);
  // line_sensor_BR = analogRead(line_sensor_BR_PIN);
  // line_sensor_FR = analogRead(line_sensor_FR_PIN);
  // NEED TO CHANGE TO VEX!

  if (line_sensor_FL > LINE_SENSOR_THRESHOLD){
    line_sensor_FL = HIGH;
  }
  else{
    line_sensor_FL = LOW;
  }
  if (line_sensor_BL > LINE_SENSOR_THRESHOLD){
    line_sensor_BL = HIGH;
  }
  else{
    line_sensor_BL = LOW;
  }
  if (line_sensor_BR > LINE_SENSOR_THRESHOLD){
    line_sensor_BR = HIGH;
  }
  else{
    line_sensor_BR = LOW;
  }
  if (line_sensor_FR > LINE_SENSOR_THRESHOLD){
    line_sensor_FR = HIGH;
  }
  else{
    line_sensor_FR = LOW;
  }
}

float distance_voltage(int sensor_value){
  float si_value = sensor_value * VOLTAGE_SCALE;
  return si_value;
}

