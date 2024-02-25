#include "ball_detection.h"
#include "motors.h"

//add more includes for some of the functions used inside these functions later if needed
#define LOWER_THRESHOLD 20      //lower threshold of long dist sensor 20 cm (example only)
#define UPPER_THRESHOLD 50      //upper threshold of long dist sensor 50 cm (example only)
#define SHORT_DIST_THRESHOLD 20 //upper threshold of short dist sensor 20 cm (example only). Make this <= LOWER_THRESHOLD
#define VOLTAGE_SCALE (5.0/1023.0)
#define RAD_TO_DEG (180.0 / PI)
#define x 15.0 //approx distance between the object detected by the left/right sensor wrt the center of ball collection mechanism in an axis perpendicular to robot direction. 15 cm is example only.
#define TOLERANCE 5.0
#define CLOSENESS 0.90

float sense_long_distance(int pin_num){
  float dist;
  voltage = analogRead(pin_num) * VOLTAGE_SCALE;
  
  //calculation for the long distance sensor here
  
  return dist;
}

float sense_short_distance(int pin_num){
  float dist;
  voltage = analogRead(pin_num) * VOLTAGE_SCALE;
  
  //calculation for the short distance sensor here
  
  return dist;
}

int read_long_status(int pin_num){
  //sense_long_distance is a function that returns the distance (in cm) of the long range analog sensor reading
  if(sense_long_distance(pin_num) <= LOWER_THRESHOLD){
    return 1; //close range
  }else if(sense_long_distance(pin_num) > UPPER_THRESHOLD){
    return 0; //far, ignore detection
  }else{
    return 2; //detected in optimum range
  }
}

int read_short_status(int pin_num){
  //sense_long_distance is a function that returns the distance (in cm) of the long range analog sensor reading
  if(sense_short_distance(pin_num) <= SHORT_DIST_THRESHOLD){
    return 1; //detected
  }else{
    return 0; //no detection
  }
}


void change_search_position(){
  //After not detecting any ball, move to a different spot.
  //This will depend on our strategy and edge detection, etc later on
}


int detect_ball(bool startup_phase){
  //In the main code, declare a boolean for startup_phase parameter.
  //Pass true if we just started this function for timing purposes. Afterwards, pass false for the same searching instant
  
  //Rotate in place and search for ball
  if(startup_phase){
    robot_move(linear_velocity = 0, angular_velocity = 120); //rotate ccw, try find detection
    search_timer = millis();
  }
  
  //Read distance sensors
  l_status = read_long_status(l_long_pin);
  r_status = read_long_status(r_long_pin);
  c_top_status = read_long_status(c_long_pin);
  c_bot_status = read_short_status(c_short_pin);

  //Find and go to ball, try to ignore opp robot

  if(abs(sense_short_distance(c_short_pin) - sense_long_distance) > TOLERANCE && c_bot_status == 1){ //ball immediately in front
    robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
    return 4;

  }else if(abs(sense_short_distance(c_short_pin) - sense_long_distance) > TOLERANCE && (l_status!=0 || r_status != 0)){
    //2 different objects detected, left and right, check the closer one first
    if(l_status!=0 && r_status != 0){
      if(sense_long_distance(r_long_pin) < sense_long_distance(l_long_pin)){
        robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement

        if(r_status == 1){
          return 21;
        }else{
          return 22;
        }
        
      }else{
        robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
          
        if(l_status == 1){
          return 31;
        }else{
          return 32;
        }
      }
      
    }else if(l_status!=0){ //object detected on the left
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      if(l_status == 1){
        return 31;
      }else{
        return 32;
      }
      
    }else{ //object detected on the right
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
        
      if(r_status == 1){
        return 21;
      }else{
        return 22;
      }
    }
  }else{ //no ball detected, continue searching
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
        float y = sense_long_distance(r_long_pin);
    
        //math to go to the detection
        double radian = atan(x/y);
        //double degree = radian * RAD_TO_DEG;
        float radius = y*y/x;
        radius += x;

        float v_translation = round(PI/2*radius, 3);
        float time_setting = radian * CLOSENESS / PI * 2;
        robot_move(linear_velocity = v_translation, angular_velocity = -90); //rotate cw
    }
  }else if(status//10 == 3){ //ball on the left
    if(status%10 == 1){ //ball is close
        robot_move(linear_velocity = 0, angular_velocity = 90); //rotate ccw
        float time_setting = 1200;
    }else{ //ball is within optimum range
        float y = sense_long_distance(r_long_pin);
    
        //math to go to the detection
        double radian = atan(x/y);
        //double degree = radian * RAD_TO_DEG;
        float radius = y*y/x;
        radius += x;

        float v_translation = round(PI/2*radius, 3);
        float time_setting = radian * CLOSENESS / PI * 2;
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
    if(abs(sense_short_distance(c_short_pin) - sense_long_distance) > TOLERANCE && c_bot_status == 1){ //ball immediately in front
      return 4;
    }else if(abs(sense_short_distance(c_short_pin) - sense_long_distance) < TOLERANCE && c_bot_status == 1){ //most likely opp
      return 5;
    }else{
      return 0; //Timeout without any detection
    }
  }else{ //if found on the way
    //found condition
    if(abs(sense_short_distance(c_short_pin) - sense_long_distance) > TOLERANCE && c_bot_status == 1){ //ball immediately in front
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      return 4;
    }else if(abs(sense_short_distance(c_short_pin) - sense_long_distance) < TOLERANCE && c_bot_status == 1 && sense_short_distance(c_short_pin) < 3.0){ //most likely blocked by opp
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      return 5;
    }else{
      return 6;
    }
  }
  //return codes
  //0 -> Timeout -> main code should execute change_search_position()
  //4 -> Ready for collection -> main code should execute ball_collection()
  //5 -> False detection. It is opponent's robot most likely -> decide on what to do
  //6 -> In process of moving
}
