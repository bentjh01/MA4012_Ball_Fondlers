#include "../config.h"
// @ShaDowFrost2417
/*
1. Search for the ball e.g. by turning around 
2. Write a check-if-ball-is-detected function to check if ball is detected and differentiate between ball and opponent
*/

//TODO!!!
//Check if the robot_move() still accepts linear and angular velocity!
int startup_phase = 1;
float robot_moving_timeout_centisecond;
int changing_search_position = 0;

int opponent_detected(float short_sensor_dist){
  if(short_sensor_dist <= OPP_CLOSENESS_THRESHOLD){
    //Theres an opp robot close in front
    return OPP_DETECTED;
  }
  else{
    return 0;
  }
}

int ball_detected(float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float short_sensor_dist){
    // may need to move this to components into sensors.c
    // Returns 1 if a ball is detected, 0 otherwise
    // return 0 when opponent is detected
    if (left_sensor_dist <= BALL_THRESHOLD_LNR || right_sensor_dist <= BALL_THRESHOLD_LNR){
        return 1;
    }
    else if(mid_sensor_dist <= BALL_THRESHOLD_MID && opponent_detected(short_sensor_dist) == 0){
        return 1;
    }
    else{
        return 0;
    }
}


int search_task(float x, float y, float yaw, float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float short_sensor_dist){
  //Scanning
  if(changing_search_position == 0){
    //Rotate to scan
    if(startup_phase){
      startup_phase = 0;
      robot_move(linear_velocity = 0, angular_velocity = 120); //rotate ccw 120 deg/s, try find detection
      search_timer = time10[T2];
      robot_moving_timeout_centisecond = 300;
    }

    //check timeout (360 deg rotation achieved)
    if(time10[T2]-search_timer > robot_moving_timeout_centisecond){
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      startup_phase = 1;
      changing_search_position = 1;
      return 0;
    }

    //check for ball
    if (ball_detected(left_sensor_dist,right_sensor_dist, mid_sensor_dist, short_sensor_dist) == 1){
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      startup_phase = 1;
      return GOTO_BALL;
    }
    else{
      //return opponent_detected(short_sensor_dist) //use this if want to check for opp robot instead of return 0;
      return 0;
    }
  }
  //Changing search position
  else{
    if(startup_phase){
      startup_phase = 0;
      robot_move(linear_velocity = 50, angular_velocity = 0); //move forward
      search_timer = time10[T2];
      robot_moving_timeout_centisecond = 160;
    }

    //check timeout (finished moving to a new search position)
    if(time10[T2]-search_timer > robot_moving_timeout_centisecond){
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      startup_phase = 1;
      changing_search_position = 0;
      return 0;
    }

    //check for ball
    if (ball_detected(left_sensor_dist,right_sensor_dist, mid_sensor_dist, short_sensor_dist) == 1){
      robot_move(linear_velocity = 0, angular_velocity = 0); //stop movement
      startup_phase = 1;
      changing_search_position = 0;
      return GOTO_BALL;
    }
    else{
      return opponent_detected(short_sensor_dist) //check for opp robot
    }
  }
    
}