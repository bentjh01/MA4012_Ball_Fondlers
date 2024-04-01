#include "../config.h"
// @ShaDowFrost2417
/*
1. Search for the ball e.g. by turning around 
2. Write a check-if-ball-is-detected function to check if ball is detected and differentiate between ball and opponent
*/

static int search_startup_phase = 1;
static int changing_search_position = 0;
static int search_counter = 0;
static float search_initial_yaw;
static float search_initial_x;
static float search_initial_y;

//NOTE!!!
//MOVE OPP DETECTION TO 
//MAIN CODE GET SENSOR READING IN CM

// int search_opponent_detected(float short_sensor_dist){
//   // may need to move this to components into sensors.c
//   if(short_sensor_dist <= OPP_CLOSENESS_THRESHOLD){
//     //Theres an opp robot close in front
//     return OPP_DETECTED;
//   }
//   else{
//     return 0;
//   }
// }

int ball_detected(float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float short_sensor_dist, int opp_detected){
  // Returns 1 if a ball is detected, 0 otherwise
  // return 0 when there is no detection
  //ignore opp robot
  if (left_sensor_dist <= BALL_THRESHOLD_LNR || right_sensor_dist <= BALL_THRESHOLD_LNR){
    return 1;
  }
  else if(mid_sensor_dist <= BALL_THRESHOLD_MID && !opp_detected){
    return 1;
  }
  else{
    return 0;
  }
}


int search_task(float x, float y, float yaw, float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float short_sensor_dist, int opp_detected){
  //Scanning
  if(changing_search_position == 0){
    //Rotate to scan
    if(search_startup_phase){
      search_startup_phase = 0;                                 //set search_startup_phase
      robot_move(linear_velocity = 0, angular_velocity = 120);  //rotate ccw 120 deg/s, try find detection
      search_initial_yaw = yaw;                                 //initialize yaw
      search_counter = 0;                                       //reset counter
    }

    //check if 360 deg rotation achieved
    if(fabs(yaw-search_initial_yaw) < SEARCH_YAW_TOLERANCE && search_counter >= SEARCH_COUNT_THRESHOLD){
      robot_move(linear_velocity = 0, angular_velocity = 0);  //stop movement
      search_startup_phase = 1;                               //reset search_startup_phase
      changing_search_position = 1;                           //initiate change search position
      return SEARCH_BALL;
    }

    //check for ball
    if (ball_detected(left_sensor_dist,right_sensor_dist, mid_sensor_dist, short_sensor_dist, opp_detected) == 1){
      robot_move(linear_velocity = 0, angular_velocity = 0);  //stop movement
      search_startup_phase = 1;                               //reset search_startup_phase
      return GOTO_BALL;
    }
    else{
      search_counter += 1; //increment counter
      //return search_opponent_detected(short_sensor_dist) //use this if want to check for opp robot instead of return 0;
      return SEARCH_BALL;
    }
  }
  //Changing search position
  else{
    if(search_startup_phase){
      search_startup_phase = 0;                               //set search_startup_phase
      robot_move(linear_velocity = 50, angular_velocity = 0); //move forward

      //initialize position
      search_initial_x = x;
      search_initial_y = y;
    }

    //check timeout (finished moving to a new search position)
    if(sqrt(pow(x-search_initial_x, 2) + pow(y-search_initial_y, 2)) < CHANGE_POSITION_DISTANCE){
      robot_move(linear_velocity = 0, angular_velocity = 0);  //stop movement
      search_startup_phase = 1;                               //reset search_startup_phase
      changing_search_position = 0;                           //terminate change_search_position
      return SEARCH_BALL;
    }

    //check for ball and opp
    if (ball_detected(left_sensor_dist,right_sensor_dist, mid_sensor_dist, short_sensor_dist, opp_detected) == 1){
      robot_move(linear_velocity = 0, angular_velocity = 0);  //stop movement
      search_startup_phase = 1;                               //reset search_startup_phase
      changing_search_position = 0;                           //terminate change_search_position
      return GOTO_BALL;
    }
    else{
      // return search_opponent_detected(short_sensor_dist) //check for opp robot
      return SEARCH_BALL;
    }
  }
    
}