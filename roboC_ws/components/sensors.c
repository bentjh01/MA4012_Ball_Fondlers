#include "../config.h"
#include "support.c"

static float prev_line_FL_val;
static float prev_line_BL_val;
static float prev_line_BR_val;
static float prev_line_FR_val;

static float prev_dis_L_val;
static float prev_dis_R_val;
static float prev_dis_mid_val;
static float prev_dis_top_val;

float filter_line_FL(float input){
	prev_line_FL_val = input;
	return low_pass_filter(input, prev_line_FL_val, FILTER_GAIN_LINE_FL);
}
float filter_line_BL(float input){
	prev_line_BL_val = input;
	return low_pass_filter(input, prev_line_BL_val, FILTER_GAIN_LINE_BL);
}
float filter_line_BR(float input){
	prev_line_BR_val = input;
	return low_pass_filter(input, prev_line_BR_val, FILTER_GAIN_LINE_BR);
}
float filter_line_FR(float input){
	prev_line_FR_val = input;
	return low_pass_filter(input, prev_line_FR_val, FILTER_GAIN_LINE_FR);
}

float filter_distance_L(float input){
	prev_dis_L_val = input;
	return low_pass_filter(input, prev_dis_L_val, FILTER_GAIN_LONG_L);
}
float filter_distance_R(float input){
	prev_dis_R_val = input;
	return low_pass_filter(input, prev_dis_R_val, FILTER_GAIN_LONG_R);
}
float filter_distance_mid(float input){
	prev_dis_mid_val = input;
	return low_pass_filter(input, prev_dis_mid_val, FILTER_GAIN_LONG_MID);
}
float filter_distance_top(float input){
	prev_dis_top_val = input;
	return low_pass_filter(input, prev_dis_top_val, FILTER_GAIN_SHORT_TOP);
}


/**
 * @brief The compass provided is discrete. This returns the current bearing of the robot
 * @param north_pin th digital reading of the pin associted with NORTH
 * @param south_pin th digital reading of the pin associted with SOUTH
 * @param east_pin th digital reading of the pin associted with EAST
 * @param west_pin th digital reading of the pin associted with WEST
 * @return the bearing of the compass
*/
float read_compass(int north_pin, int south_pin, int east_pin, int west_pin){
  int combination = north_pin << 3 + south_pin  << 2 + east_pin  << 1 + west_pin;
  switch (combination)
  {
    case 0b0111:
      return NORTH;
    case 0b1011:
      return SOUTH;
    case 0b1101:
      return EAST;
    case 0b1110:
      return WEST;
    case 0b0101:
      return NORTH_EAST;
    case 0b0110:
      return NORTH_WEST;
    case 0b1001:
      return SOUTH_EAST;
    case 0b1010:
      return SOUTH_WEST;
    default:
      return NULL;
  }
}

/**
 * @brief The function to convert miliVolts to the distance value of the long distance sensor
 * @param sensor_val miliVolt of analog reading. ROBOTC's SensorValue returns miliVolts
 * @return distance in [cm]
*/
float calculate_long_distance(float sensor_val){
  float voltage = sensor_val * mVOLT_TO_VOLT;

  //step-by-step calculation as arduino cannot handle PEMDAS
  float ln_voltage = log(voltage);
  float ln_voltage_square = ln_voltage*ln_voltage;
  float term_1 = 29.971*ln_voltage;
  float term_2 = 55.047*ln_voltage_square;
  float term_3 = 57.931*voltage;
  float distance_cm = term_1 + term_2 - term_3 + 84.019;
  return distance_cm;
}

/**
 * @brief The function to convert miliVolts to the distance value of the short distance sensor
 * @param sensor_val miliVolt of analog reading. ROBOTC's SensorValue returns miliVolts
 * @return distance in [cm]
*/
float calculate_short_distance(float sensor_val){
  float voltage = sensor_val * mVOLT_TO_VOLT;

  //calculation for the short distance sensor here
  float exponent = -1/0.95;
  float base = voltage/11.033;
  float distance_cm = pow(base, exponent);
  return distance_cm;
}

/// @brief Checks for ball in chamber using the middle short distance sensor
/// @param mid_sensor_distance 
/// @return TRIGGERED for ball in chamber, NOT_TRIGGERED for no ball in chamber
int check_ball_in_chamber(float mid_sensor_distance){
  if (mid_sensor_distance < BALL_IN_CHAMBER_DISTANCE){
    return TRIGGERED;
  }
  else{
    return NOT_TRIGGERED;
  }
}

/// @brief Checks the threshold of a sensor
/// @param sensor_val current sensor value
/// @param threshold
/// @return TRIGGERED if sensor_val > threshold, NOT_TRIGGERED otherwise
int check_threshold(float sensor_val, float threshold){
  if (sensor_val > threshold){
    return TRIGGERED;
  }
  else{
    return NOT_TRIGGERED;
  }
}