#include "ball_detection.h"

float search_timer;
float robot_moving_timeout_milisecond;

int check_status_from_left_right_sensor(int long_distance_sensor_FL_status, int long_distance_sensor_FR_status){
  /*
  Check which direction to go to (left or right) and whether only rotation is needed or need translation too
  21 -> Potential ball found on the right, only rotation needed -> main code should execute go_to_detection(21)
  22 -> Potential ball found on the right, need translation and rotation -> main code should execute go_to_detection(22)
  31 -> Potential ball found on the left, only rotation needed -> main code should execute go_to_detection(31)
  32 -> Potential ball found on the left, need translation and rotation -> main code should execute go_to_detection(32)
  */
  if(long_distance_sensor_FL_status!=0 && long_distance_sensor_FR_status != 0){
    //both have detection, go to the closer one
    if(read_long_sensor_distance_CM(long_distance_sensor_FR_pin) < read_long_sensor_distance_CM(long_distance_sensor_FL_pin)){
      //stop movement
      robot_move(linear_velocity = 0, angular_velocity = 0);
      //check if the ball is close enough for just pure rotation
      if(long_distance_sensor_FR_status == 1){
        return 21;
      }
      else{
        return 22;
      }
    }
    else{
      //stop movement
      robot_move(linear_velocity = 0, angular_velocity = 0);
      //check if the ball is close enough for just pure rotation
      if(long_distance_sensor_FL_status == 1){
        return 31;
      }
      else{
        return 32;
      }
    }
  }
  else if(long_distance_sensor_FL_status!=0){ //object detected on the left
    //stop movement
    robot_move(linear_velocity = 0, angular_velocity = 0);
    //check if the ball is close enough for just pure rotation
    if(long_distance_sensor_FL_status == 1){
      return 31;
    }
    else{
      return 32;
    } 
  }
  else{ //object detected on the right
    //stop movement
    robot_move(linear_velocity = 0, angular_velocity = 0);
    //check if the ball is close enough for just pure rotation
    if(long_distance_sensor_FR_status == 1){
      return 21;
    }
    else{
      return 22;
    }
  }
}

circular_path calculate_translation_angular_speed(int pin_num, float angular_velocity_DegPerSec){
  circular_path path;
  float dist_from_robot = read_long_sensor_distance_CM(pin_num);

  //math to go to the detection
  double radian = atan(BALL_TO_ROBOT_CENTER/dist_from_robot);
  float radius = dist_from_robot*dist_from_robot/BALL_TO_ROBOT_CENTER;
  radius += BALL_TO_ROBOT_CENTER;

  path.angular_velocity = angular_velocity_DegPerSec;
  float omega = abs(angular_velocity_DegPerSec/180.0*PI);
  path.linear_velocity = round(omega*radius, 3);
  path.time_setting_milisecond = round(radian * FRACTIONAL_CLOSENESS_TO_BALL / omega * 1000, 3); //t = theta/omega, correct to 3 dp
  return path;
}

int change_search_position(bool startup_phase){
  //optimal detection range for both long distance sensor is only up to 45 cm.
  //giving arnd 10 cm overlap between 2 consecutive scan areas, we can move the robot 80 cm forward, and set that position as the new search position
  if(startup_phase){
    robot_move(linear_velocity = 50, angular_velocity = 0); //move forward
    search_timer = time10[centis];
    robot_moving_timeout_milisecond = 1600;
  }

  if(time10[centis]-search_timer > robot_moving_timeout_milisecond){
    //movement finished, stop movement
    robot_move(linear_velocity = 0, angular_velocity = 0);
    return 0;
  }
  else{
    return 1;
  }

  //return codes
  //0 -> Timeout (position reached) -> main code should execute scan(1)
  //1 -> Still moving
}

int scan(bool startup_phase){
  //In the main code, declare a boolean for startup_phase parameter.
  //Pass true if we just started this function for timing purposes. Afterwards, pass false for the same searching instant
  
  //Rotate in place and search for ball
  if(startup_phase){
    robot_move(linear_velocity = 0, angular_velocity = 120); //rotate ccw, try find detection
    search_timer = time10[centis];
  }
  
  //Read distance sensors
  long_distance_sensor_FL_status = read_digitized_long_sensor_distance(long_distance_sensor_FL_pin);
  long_distance_sensor_FR_status = read_digitized_long_sensor_distance(long_distance_sensor_FR_pin);
  //long_distance_sensor_TP_status = read_digitized_long_sensor_distance(long_distance_sensor_TP_pin);
  short_distance_sensor_status = read_digitized_short_sensor_distance(short_distance_sensor_pin);

  
  //Find and go to ball, try to ignore opp robot
  if(short_distance_sensor_status == 1){
    //if ball immediately in front
    robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
    return 4;
  }
  else if(abs(read_short_sensor_distance_CM(short_distance_sensor_pin) - read_long_sensor_distance_CM(long_distance_sensor_TP_pin)) > TOLERANCE_CM && (long_distance_sensor_FL_status!=0 || long_distance_sensor_FR_status != 0)){
    //if ball is detected on left or right
    return check_status_from_left_right_sensor(long_distance_sensor_FL_status, long_distance_sensor_FR_status)
  }
  else{
    //no ball detected, check if timeout. Else continue searching
    if(time10[centis]-search_timer > 3000){
      return 0
    }
    else{
      return 1;
    }
  }
  //return codes
  //0 -> Timeout -> main code should execute change_search_position()
  //1 -> Searching
  //21 -> Potential ball found on the right, only rotation needed -> main code should execute go_to_detection(21,1)
  //22 -> Potential ball found on the right, need translation and rotation -> main code should execute go_to_detection(22,1)
  //31 -> Potential ball found on the left, only rotation needed -> main code should execute go_to_detection(31,1)
  //32 -> Potential ball found on the left, need translation and rotation -> main code should execute go_to_detection(32,1)
  //4 -> Ready for collection -> main code should execute ball_collection()
}


int go_to_detection(int status, bool startup_phase){
  if(startup_phase){
    search_timer = time10[centis];
    switch(status){
      case 21:
      {
        //ball on the right, only rotation needed
        robot_move(linear_velocity = 0, angular_velocity = -90); //rotate cw
        robot_moving_timeout_milisecond = 1200;
      }
      case 22:
      {
        circular_path path = calculate_translation_angular_speed(long_distance_sensor_FR_pin,-90);
        robot_moving_timeout_milisecond = path.time_setting_milisecond;
        robot_move(linear_velocity = path.linear_velocity, angular_velocity = path.angular_velocity); //rotate cw
      }
      case 31:
      {
        robot_move(linear_velocity = 0, angular_velocity = 90); //rotate ccw
        robot_moving_timeout_milisecond = 1200;
      }
      case 32:
      {
        circular_path path = calculate_translation_angular_speed(long_distance_sensor_FL_pin,90);
        robot_moving_timeout_milisecond = path.time_setting_milisecond;
        robot_move(linear_velocity = path.linear_velocity, angular_velocity = path.angular_velocity); //rotate cw
      }
    }
  }

  //found condition
  //ball immediately in front
  if(short_distance_sensor_status == 1){
    robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
    return 4;
  }
  //most likely blocked by opp
  else if(abs(read_short_sensor_distance_CM(short_distance_sensor_pin) - read_long_sensor_distance_CM(long_distance_sensor_TP_pin)) < TOLERANCE_CM && short_distance_sensor_status == 1){
    //CHANGE THE OPP ROBOT DETECTION
    robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
    return 5;
  }
  else{
    //Timeout
    if(time10[centis]-search_timer > robot_moving_timeout_milisecond){
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      return 0;
    }
    //still in progress of moving
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
