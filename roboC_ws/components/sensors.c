#include "../config.h"
#include "support.c"

float filter_line_FL(float input){
  static float prev_line_FL_val;
	float output = low_pass_filter(input, prev_line_FL_val, FILTER_GAIN_LINE_FL);
	prev_line_FL_val = output;
	return output;
}
float filter_line_BL(float input){
	static float prev_line_BL_val;
	float output = low_pass_filter(input, prev_line_BL_val, FILTER_GAIN_LINE_BL);
	prev_line_BL_val = output;
	return output;
}
float filter_line_BR(float input){
	static float prev_line_BR_val;
	float output = low_pass_filter(input, prev_line_BR_val, FILTER_GAIN_LINE_BR);
	prev_line_BR_val = output;
  return output;
}
float filter_line_FR(float input){
	static float prev_line_FR_val;
	float output = low_pass_filter(input, prev_line_FR_val, FILTER_GAIN_LINE_FR);
    prev_line_FR_val = output;
	return output;
}

float filter_distance_L(float input){
	static float prev_dis_L_val;
	float output = low_pass_filter(input, prev_dis_L_val, FILTER_GAIN_LONG_L);
	prev_dis_L_val = output;
	return output;
}
float filter_distance_R(float input){
	static float prev_dis_R_val;
	float output = low_pass_filter(input, prev_dis_R_val, FILTER_GAIN_LONG_R);
	prev_dis_R_val = output;
  return output;
}
float filter_distance_mid(float input){
	static float prev_dis_mid_val;
	float output = low_pass_filter(input, prev_dis_mid_val, FILTER_GAIN_LONG_MID);
	prev_dis_mid_val = output;
	return output;
}
float filter_distance_top(float input){
	static float prev_dis_top_val;
	float output = low_pass_filter(input, prev_dis_top_val, FILTER_GAIN_SHORT_TOP);
	prev_dis_top_val = output;
  return output;
}

float filter_encoderL(float en_rpmL){
  static float prev_en_rpmL;
  float output = low_pass_filter(en_rpmL, prev_en_rpmL, FILTER_ENCODER);
  prev_en_rpmL = output;
  return output;
}

float filter_encoderR(float en_rpmR){
  static float prev_en_rpmR;
  float output = low_pass_filter(en_rpmR, prev_en_rpmR, FILTER_ENCODER);
  prev_en_rpmR = output;
  return output;
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
  int combination = north_pin * 1000 + south_pin  * 100 + east_pin  *10 + west_pin;
  if (combination == 0111){
    return NORTH;
  }
  else if (combination == 1011){
    return SOUTH;
  }
  else if (combination == 1101){
    return EAST;
  }
  else if (combination == 1110){
    return WEST;
  }
  else if (combination == 0101){
    return NORTH_EAST;
  }
  else if (combination == 0110){
    return NORTH_WEST;
  }
  else if (combination == 1001){
    return SOUTH_EAST;
  }
  else if (combination == 1010){
    return SOUTH_WEST;
  }
  else {
    return INVALID;
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
  // if (sensor_val < threshold){
  if (sensor_val > threshold){ // TESTING
    return TRIGGERED;
  }
  else{
    return NOT_TRIGGERED;
  }
}

int opponent_detection(float short_sensor_dist){
  // may need to move this to components into sensors.c
  if(short_sensor_dist <= OPP_CLOSENESS_THRESHOLD){
    //Theres an opp robot close in front
    return 1;
  }
  else{
    return 0;
  }
}

int detect_ball(float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float top_sensor_dist, int opp_detected){
  // Returns 1 if a something that is not an opponent is detected, 0 otherwise
  // return 0 when there is no detection
	//THE ORDER OF CHECK MATTERS!
  if (mid_sensor_dist <= BALL_THRESHOLD_MID && !opp_detected){
    return 1;
  }
  else if(mid_sensor_dist <= BALL_THRESHOLD_MID && opp_detected && fabs(mid_sensor_dist-top_sensor_dist) > OPP_DIFFERENTIATION_THRESHOLD){
    return 1;
  }
  else if(mid_sensor_dist <= BALL_THRESHOLD_MID && opp_detected && fabs(mid_sensor_dist-top_sensor_dist) <= OPP_DIFFERENTIATION_THRESHOLD){
    return 0;
  }
  else if(left_sensor_dist <= BALL_THRESHOLD_LNR || right_sensor_dist <= BALL_THRESHOLD_LNR){
  	return 1;
  }
  else{
    return 0;
  }
}

/// @brief Checks if sensor detects a ball by a large reduction in distance reading
/// @param left_sensor_dist
/// @return 0 if no detection, Distance reading if detection
float detect_ball_left(float left_sensor_dist){
  static float prev_left;
  float dr = prev_left-left_sensor_dist;
  float result;
  left_sensor_dist = min(left_sensor_dist, LIMIT_DISTANCE_READINGS);
  // falling edge i.e. high to low
  if (dr >= BALL_THRESHOLD_CHANGE){
    result = prev_left;
  }
  else{
    result = 0;
  }
  prev_left = left_sensor_dist;
  return result;
}

/// @brief Checks if sensor detects a ball by a large reduction in distance reading
/// @param right_sensor_dist
/// @return 0 if no detection, Distance reading if detection
float detect_ball_right(float right_sensor_dist){
  static float prev_right;
  float dr = prev_right-right_sensor_dist;
  float result;
  prev_right = right_sensor_dist;
  right_sensor_dist = min(right_sensor_dist, LIMIT_DISTANCE_READINGS);
  // falling edge i.e. high to low
  if (dr >= BALL_THRESHOLD_CHANGE){
    result = prev_right;
  }
  else{
    result = 0;
  }
  prev_right = right_sensor_dist;
  return result;
}

/// @brief Checks if sensor detects a ball or to ignore the detection if it is the opponent robot
/// @param mid_sensor_dist
/// @param top_sensor_dist
/// @return 0 if no detection, Distance reading if detection
float detect_ball_mid(float mid_sensor_dist, float top_sensor_dist){
  static float prev_mid;
  float dr = prev_mid-mid_sensor_dist;
  float result;
  mid_sensor_dist = min(mid_sensor_dist, LIMIT_DISTANCE_READINGS);
  top_sensor_dist = min(top_sensor_dist, LIMIT_DISTANCE_READINGS); // TODO Please check if this is correct

  // if (fabs(mid_sensor_dist - top_sensor_dist) > OPP_DETECT_THRESHOLD){
  if (opponent_detection(top_sensor_dist)==1){
    result = 0;
  }
  // falling edge i.e. high to low
  else if (dr >= BALL_THRESHOLD_CHANGE){
    result = prev_mid;
  }
  else{
    result = 0;
  }

  prev_mid = mid_sensor_dist;
  return result;
}

/// @brief Checks if the back wall is detected or if a flat surface is detected by comparing the mean of the left and right sensors with the middle sensor.
/// @param left_sensor
/// @param right_sensor
/// @param mid_sensor
/// @return TRIGGERED if back wall is detected, NOT_TRIGGERED otherwise
int detect_back_wall(float left_sensor, float right_sensor, float mid_sensor){
  left_sensor = min(left_sensor, LIMIT_DISTANCE_READINGS);
  right_sensor = min(right_sensor, LIMIT_DISTANCE_READINGS);
  mid_sensor = min(mid_sensor, LIMIT_DISTANCE_READINGS);

  float expected_mid_distance = (left_sensor + right_sensor)/2.0;
  if (fabs(mid_sensor - expected_mid_distance) < FLAT_SURFACE_THRESHOLD){
  	if (expected_mid_distance >= LIMIT_DISTANCE_READINGS){
  		return NOT_TRIGGERED;
  	}
    return TRIGGERED;
  }
  else{
    return NOT_TRIGGERED;
  }

  // if (fabs(left_sensor - right_sensor) < FLAT_SURFACE_THRESHOLD){
  //   return TRIGGERED;
  // }
  // else{
  //   return NOT_TRIGGERED;
  // }
}