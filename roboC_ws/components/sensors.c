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
	static float prev_left_out;
  static float prev_left1;
  static float prev_left2;
  float output = median_filtering(input, prev_left1, prev_left2);
	output = low_pass_filter(output, prev_left_out, FILTER_GAIN_LONG_R);
  prev_left_out = output;
  prev_left1 = input;
  prev_left2 = prev_left1;
	return output;
}

float filter_distance_R(float input){
	static float prev_right_out;
  static float prev_right1;
  static float prev_right2;
  float output = median_filtering(input, prev_right1, prev_right2);
	output = low_pass_filter(output, prev_right_out, FILTER_GAIN_LONG_R);
  prev_right_out = output;
  prev_right1 = input;
  prev_right2 = prev_right1;
	return output;
}

float filter_distance_mid(float input){
	static float prev_mid_out;
  static float prev_mid1;
  static float prev_mid2;
	// float output = low_pass_filter(input, prev_dis_mid_val, FILTER_GAIN_LONG_MID);
	// prev_dis_mid_val = output;
  float output = median_filtering(input, prev_mid1, prev_mid2);
	output = low_pass_filter(output, prev_mid_out, FILTER_GAIN_LONG_MID);
  prev_mid_out = output;
  prev_mid1 = input;
  prev_mid2 = prev_mid1;
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

/// @brief Checks the threshold of a sensor
/// @param sensor_val current sensor value
/// @param threshold
/// @return TRIGGERED if sensor_val < threshold, NOT_TRIGGERED otherwise
int check_threshold(float sensor_val, float threshold){
  if (sensor_val < threshold){
  // if (sensor_val > threshold){ // TESTING
    return TRIGGERED;
  }
  else{
    return NOT_TRIGGERED;
  }
}

/// @brief Checks if an opponent is detected 
/// @param short_sensor_dist 
/// @param limit_dist 
/// @return 1 if opponent is within the threshold, 0 if not 
int opponent_detection(float short_sensor_dist, float limit_dist){
  // may need to move this to components into sensors.c
  if(short_sensor_dist <= limit_dist){
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

/**
 * Checks for detection based on sensor readings.
 * 
 * @param yaw The yaw angle of the robot.
 * @param left_sensor_dist The distance reading from the left sensor.
 * @param right_sensor_dist The distance reading from the right sensor.
 * @param mid_sensor_dist The distance reading from the middle sensor.
 * @param top_sensor_dist The distance reading from the top sensor.
 * @param limit_dist The maximum distance threshold.
 * @return An integer representing the detection result:
 *         - OPPONENT_DETECTED: If an opponent is detected.
 *         - WALL_DETECTED: If a wall is detected.
 *         - BALL_MIDDLE_DETECTED: If a ball is detected in the middle.
 *         - BALL_LEFT_DETECTED: If a ball is detected on the left.
 *         - BALL_RIGHT_DETECTED: If a ball is detected on the right.
 *         - -1: If no detection is made.
 */
int check_detection(float yaw, float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float top_sensor_dist, float limit_dist){
  left_sensor_dist = min(left_sensor_dist, limit_dist);
  right_sensor_dist = min(right_sensor_dist, limit_dist);
  mid_sensor_dist = min(mid_sensor_dist, limit_dist);
  top_sensor_dist = min(top_sensor_dist, limit_dist);

  float minimum = min(min(left_sensor_dist, right_sensor_dist), mid_sensor_dist);

  int detectedLeft = check_threshold(left_sensor_dist, limit_dist);
  int detectedRight = check_threshold(right_sensor_dist, limit_dist);
  int detectedMid = check_threshold(mid_sensor_dist, limit_dist);
  int detectedTop = check_threshold(top_sensor_dist, limit_dist);

  /// check for opponent
  if (detectedMid == TRIGGERED && detectedTop == TRIGGERED){
    if (top_sensor_dist == minimum){
      return OPPONENT_DETECTED;
    }
  }

  if (detectedLeft == TRIGGERED || detectedRight == TRIGGERED || detectedMid == TRIGGERED){
    // check for wall
    if (fabs(yaw) > 135.0){
      // robot is facing the back wall
      if (detectedLeft == TRIGGERED && detectedRight == TRIGGERED && detectedMid == TRIGGERED){
        // all 3 sensors are triggered
        // the expected distance of the middle sensor is the distance reading from the middle sensor if the robot was facing a flat surface
        float expected_mid_distance = (left_sensor_dist + right_sensor_dist)/2.0;
        if (fabs(mid_sensor_dist - expected_mid_distance) < FLAT_SURFACE_THRESHOLD){
          return WALL_DETECTED;
        }
      }
    }
    // check for opponent
    if (detectedMid == TRIGGERED && detectedTop == TRIGGERED && top_sensor_dist <= OPP_CLOSENESS_THRESHOLD){
      return OPPONENT_DETECTED;
    }
    // ball in middle
    if (detectedMid == TRIGGERED && mid_sensor_dist == minimum){
      return BALL_MIDDLE_DETECTED;
    }
    // ball in left
    if (detectedLeft == TRIGGERED && left_sensor_dist == minimum){
      return BALL_LEFT_DETECTED;
    }
    // ball on right
    if (detectedRight == TRIGGERED && right_sensor_dist == minimum){
      return BALL_RIGHT_DETECTED;
    }
  }
  else{
    return -1;
  }
}

/**
 * Checks if a ball is in the chamber based on the arm angle and mid sensor distance.
 *
 * @param arm_angle The angle of the arm in degrees.
 * @param mid_sensor_dist The distance measured by the mid sensor in centimeters.
 * @return Returns TRIGGERED if a ball is in the chamber, otherwise returns NOT_TRIGGERED.
 */
int check_ball_in_chamber(float arm_angle, float mid_sensor_dist){
  if (arm_angle == SERVO_COLLECT_POSITION && mid_sensor_dist <= BALL_IN_CHAMBER_DISTANCE){
    return TRIGGERED;
  }
  return NOT_TRIGGERED;
}