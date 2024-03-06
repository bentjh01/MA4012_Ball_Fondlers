#include "ball_detection.h"
#include "motors.h"

float read_long_sensor_distance(int pin_num){
  float voltage = analogRead(pin_num) * VOLTAGE_SCALE;
  
  //step-by-step calculation as arduino cannot handle PEMDAS
  float ln_sharp_dist_reading = log(sharp_dist_reading);
  float ln_sharp_dist_reading_square = ln_sharp_dist_reading*ln_sharp_dist_reading;
  float term_1 = 29.971*ln_sharp_dist_reading;
  float term_2 = 55.047*(ln_sharp_dist_reading*ln_sharp_dist_reading);
  float term_3 = 57.931*sharp_dist_reading;
  float distance_cm = term_1 + term_2 - term_3 + 84.019;
  
  return distance_cm;
}

float read_short_sensor_distance(int pin_num){
  float voltage = analogRead(pin_num) * VOLTAGE_SCALE;
  
  //calculation for the short distance sensor here
  float distance_cm = pow(voltage/11.033, -1/0.95);
  return distance_cm;
}

int read_digitized_long_sensor_distance(int pin_num){
  //read_long_sensor_distance is a function that returns the distance (in cm) of the long range analog sensor reading
  if(read_long_sensor_distance(pin_num) <= LONG_DIST_LOWER_THRESHOLD_CM){
    return 1; //close range
  }
  else if(read_long_sensor_distance(pin_num) > LONG_DIST_UPPER_THRESHOLD_CM){
    return 0; //far, ignore detection
  }
  else{
    return 2; //detected in optimum range
  }
}

int read_digitized_short_sensor_distance(int pin_num){
  //read_short_sensor_distance is a function that returns the distance (in cm) of the long range analog sensor reading
  if(read_short_sensor_distance(pin_num) <= SHORT_DIST_THRESHOLD_CM){
    return 1; //detected
  }
  else{
    return 0; //no detection
  }
}


void change_search_position(){
  //After not detecting any ball, move to a different spot.
  //This will depend on our strategy and edge detection, etc later on
}


int scan(bool startup_phase)
{
  //In the main code, declare a boolean for startup_phase parameter.
  //Pass true if we just started this function for timing purposes. Afterwards, pass false for the same searching instant
  
  //Rotate in place and search for ball
  if(startup_phase){
    robot_move(linear_velocity = 0, angular_velocity = 120); //rotate ccw, try find detection
    search_timer = millis();
  }
  
  //Read distance sensors
  l_status = read_digitized_long_sensor_distance(l_long_pin);
  r_status = read_digitized_long_sensor_distance(r_long_pin);
  c_top_status = read_digitized_long_sensor_distance(c_long_pin);
  c_bot_status = read_digitized_short_sensor_distance(c_short_pin);

  //Find and go to ball, try to ignore opp robot

  if(abs(read_short_sensor_distance(c_short_pin) - read_long_sensor_distance(c_top_status)) > TOLERANCE_CM && c_bot_status == 1){
    //if ball immediately in front
    robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
    return 4;
  }
  else if(abs(read_short_sensor_distance(c_short_pin) - read_long_sensor_distance(c_top_status)) > TOLERANCE_CM && (l_status!=0 || r_status != 0)){
    //if ball is detected on left or right

    //Check which direction to turn to: left or right (if any)
    if(l_status!=0 && r_status != 0){
      //both have detection, go to the closer one
      if(read_long_sensor_distance(r_long_pin) < read_long_sensor_distance(l_long_pin)){
        robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement

        //check if the ball is close enough for just pure rotation
        if(r_status == 1){
          return 21;
        }
        else{
          return 22;
        }
      }
      else{
        robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
        if(l_status == 1){
          return 31;
        }
        else{
          return 32;
        }
      }
    }
    else if(l_status!=0){ //object detected on the left
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      if(l_status == 1){
        return 31;
      }
      else{
        return 32;
      } 
    }
    else{ //object detected on the right
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
        
      if(r_status == 1){
        return 21;
      }
      else{
        return 22;
      }
    }
  }
  else{ //no ball detected, continue searching
    return 1;
  }
  //return codes
  //0 -> Timeout -> main code should execute change_search_position()
  //1 -> Searching
  //21 -> Potential ball found on the right -> main code should execute go_to_detection(21)
  //22 -> Potential ball found on the right -> main code should execute go_to_detection(22)
  //31 -> Potential ball found on the left -> main code should execute go_to_detection(31)
  //32 -> Potential ball found on the left -> main code should execute go_to_detection(32)
  //4 -> Ready for collection -> main code should execute ball_collection()
}


int go_to_detection(int status, bool startup_phase){
  if(status//10 == 2){ //ball on the right
    
    if(status%10 == 1){ //ball is close
        robot_move(linear_velocity = 0, angular_velocity = -90); //rotate cw
        float time_setting = 1200;
    
    }else{ //ball is within optimum range
        float y = read_long_sensor_distance(r_long_pin);
    
        //math to go to the detection
        double radian = atan(BALL_TO_ROBOT_CENTER/y);
        //double degree = radian * RAD_TO_DEG;
        float radius = y*y/BALL_TO_ROBOT_CENTER;
        radius += BALL_TO_ROBOT_CENTER;

        float v_translation = round(PI/2*radius, 3);
        float time_setting = radian * FRACTIONAL_CLOSENESS_TO_BALL / PI * 2;
        robot_move(linear_velocity = v_translation, angular_velocity = -90); //rotate cw
    }
  }else if(status//10 == 3){ //ball on the left
    if(status%10 == 1){ //ball is close
        robot_move(linear_velocity = 0, angular_velocity = 90); //rotate ccw
        float time_setting = 1200;
    }else{ //ball is within optimum range
        float y = read_long_sensor_distance(r_long_pin);
    
        //math to go to the detection
        double radian = atan(BALL_TO_ROBOT_CENTER/y);
        //double degree = radian * RAD_TO_DEG;
        float radius = y*y/BALL_TO_ROBOT_CENTER;
        radius += BALL_TO_ROBOT_CENTER;

        float v_translation = round(PI/2*radius, 3);
        float time_setting = radian * FRACTIONAL_CLOSENESS_TO_BALL / PI * 2;
        robot_move(linear_velocity = v_translation, angular_velocity = 90); //rotate ccw
    }
  }

  if(startup_phase){
    search_timer = millis();
    robot_moving_timeout = time_setting;
  }


  if(millis()-search_timer > robot_moving_timeout){
    robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement

    //Final check after arriving at the destination
    if(abs(read_short_sensor_distance(c_short_pin) - read_long_sensor_distance(c_top_status)) > TOLERANCE_CM && c_bot_status == 1){ //ball immediately in front
      return 4;
    }
    else if(abs(read_short_sensor_distance(c_short_pin) - read_long_sensor_distance(c_top_status)) < TOLERANCE_CM && c_bot_status == 1){ //most likely opp
      return 5;
    }
    else{
      return 0; //Timeout without any detection
    }
  }
  else{ //if found on the way
    //found condition
    if(abs(read_short_sensor_distance(c_short_pin) - sense_long_distance) > TOLERANCE_CM && c_bot_status == 1){ //ball immediately in front
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      return 4;
    }
    else if(abs(read_short_sensor_distance(c_short_pin) - sense_long_distance) < TOLERANCE_CM && c_bot_status == 1 && read_short_sensor_distance(c_short_pin) < 3.0){ //most likely blocked by opp
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      return 5;
    }
    else{
      return 6;
    }
  }
  //return codes
  //0 -> Timeout -> main code should execute change_search_position()
  //4 -> Ready for collection -> main code should execute ball_collection()
  //5 -> False detection. It is opponent's robot most likely -> decide on what to do
  //6 -> In process of moving
}
