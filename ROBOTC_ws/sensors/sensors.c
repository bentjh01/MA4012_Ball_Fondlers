#include "sensors.h"

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
  #pragma config(Sensor, LINE_SENSOR_FL_PIN, line_sensor_FL, sensorAnalog)
  #pragma config(Sensor, LINE_SENSOR_BL_PIN, line_sensor_BL, sensorAnalog)
  #pragma config(Sensor, LINE_SENSOR_BR_PIN, line_sensor_BR, sensorAnalog)
  #pragma config(Sensor, LINE_SENSOR_FR_PIN, line_sensor_FR, sensorAnalog)

  // Long Distance Sensor
  #pragma config(Sensor, LONG_DISTANCE_SENSOR_FL_PIN, long_distance_sensor_FL, sensorAnalog)
  #pragma config(Sensor, LONG_DISTANCE_SENSOR_FR_PIN, long_distance_sensor_FR, sensorAnalog)
  #pragma config(Sensor, LONG_DISTANCE_SENSOR_TP_PIN, long_distance_sensor_TP, sensorAnalog)

  // Short Distance Sensor
  #pragma config(Sensor, SHORT_DISTANCE_SENSOR_PIN,    short_distance_sensor, sensorAnalog)

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
  long_distance_sensor_FL = long_distance_convert(long_distance_sensor_FL_PIN);
  long_distance_sensor_FR = long_distance_convert(long_distance_sensor_FR_PIN);
  long_distance_sensor_TP = long_distance_convert(long_distance_sensor_TP_PIN);
  short_distance_sensor = short_distance_convert(short_distance_sensor_PIN);
}

void read_limit_switches(void){
  limit_switch_chamber = digitalRead(limit_switch_chamber_PIN);
  limit_switch_BL = digitalRead(limit_switch_BL_PIN);
  limit_switch_BR = digitalRead(limit_switch_BR_PIN);
}

void read_compass(void){
  int PIN1 = digitalRead(magnetometer_PIN1);
  int PIN2 = digitalRead(magnetometer_PIN2);
  int PIN3 = digitalRead(magnetometer_PIN3);
  int PIN4 = digitalRead(magnetometer_PIN4);

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
  line_sensor_FL = analogRead(line_sensor_FL_PIN);
  line_sensor_BL = analogRead(line_sensor_BL_PIN);
  line_sensor_BR = analogRead(line_sensor_BR_PIN);
  line_sensor_FR = analogRead(line_sensor_FR_PIN);

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

float long_distance_convert(int sensor_value){
  float si_value = sensor_value * 5.0 / 1023.0;
  return si_value;
}
float short_distance_convert(int sensor_value){
  float si_value = sensor_value * 5.0 / 1023.0;
  return si_value;
}

