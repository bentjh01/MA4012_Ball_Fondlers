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
static float search_linX;
static float search_angZ;
static float change_position_traveled_distance;
static int search_reduce = 0.0;

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

int search_ball_detected(float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, int opp_detected){
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


int search_task(float x, float y, float yaw, float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, int opp_detected, float search_current_rpmL, float search_current_rpmR){
  //Scanning
  if(changing_search_position == 0){
    //Rotate to scan
    if(search_startup_phase){
    	//reset any movement
    	if(fabs(search_current_rpmL) > 0.0001 || fabs(search_current_rpmR) >= 0.0001){
  			search_linX = 0.0;
      	search_angZ = 0.0;
      	return SEARCH;
  		}

      search_startup_phase = 0;         //set search_startup_phase
      search_reduce = 0;		//reset search_proportional_offset

      //rotate ccw, try find detection
      //search_linX = 0.0;
      //search_angZ = 120.0;

      search_initial_yaw = yaw; //initialize yaw, correcting for momentum error 45 deg
      
      if(search_initial_yaw < -180.0){
      	search_initial_yaw = search_initial_yaw + 360;
      }
      
      search_counter = 0;              //reset counter
    }

    if((fabs(search_initial_yaw)+fabs(yaw)) >= 175.0 && (fabs(search_initial_yaw)+fabs(yaw)) <= 185.00){
    	search_reduce = 1;
    }

    if(search_reduce == 0){
    	//rotate ccw, try find detection
      search_linX = 0.0;
      search_angZ = 120.0;
    }
    else{
    	search_linX = 0.0;
      search_angZ = fabs(yaw-search_initial_yaw)/180.0*120.0;

      //if(search_angZ < 60.0){
      	//search_angZ = 60.0;
      //}
    }

    //check if 360 deg rotation achieved
    if(fabs(yaw-search_initial_yaw) < YAW_TOLERANCE && search_counter >= SEARCH_COUNT_THRESHOLD){
      //stop movement
      search_linX = 0.0;
      search_angZ = 0.0;

      search_startup_phase = 1;                               //reset search_startup_phase
      changing_search_position = 1;                           //initiate change search position
      return SEARCH;
    }

    //check for ball
    if (search_ball_detected(left_sensor_dist,right_sensor_dist, mid_sensor_dist, opp_detected) == 1){
      //stop movement
      //search_linX = 0.0;
      //search_angZ = 0.0;

      //search_startup_phase = 1;                               //reset search_startup_phase
      //return GOTO;
    	return SEARCH;
    }
    else{
      search_counter += 1; //increment counter
      //return search_opponent_detected(short_sensor_dist) //use this if want to check for opp robot instead of return 0;
      return SEARCH;
    }

  }
  //Changing search position
  else{
    if(search_startup_phase){
    	if(fabs(search_current_rpmL) > 0.0001 || fabs(search_current_rpmR) >= 0.0001){
  			search_linX = 0.0;
      	search_angZ = 0.0;
      	return SEARCH
  		}

      search_startup_phase = 0;                               //set search_startup_phase
      //move forward
      search_linX = 0.20;
      search_angZ = 0.0;

      //initialize position
      search_initial_x = x;
      search_initial_y = y;
    }

    change_position_traveled_distance = sqrt(pow(x-search_initial_x, 2) + pow(y-search_initial_y, 2);

    //check if finished moving to a new search position
    if(change_position_traveled_distance >= CHANGE_POSITION_DISTANCE){
      //stop movement
      search_linX = 0.0;
      search_angZ = 0.0;

      search_startup_phase = 1;                               //reset search_startup_phase
      changing_search_position = 0;                           //terminate change_search_position
      return SEARCH;
    }

    //check for ball and opp
    if (search_ball_detected(left_sensor_dist,right_sensor_dist, mid_sensor_dist, opp_detected) == 1){
      //stop movement
      //search_linX = 0.0;
      //search_angZ = 0.0;

      //search_startup_phase = 1;                               //reset search_startup_phase
      //changing_search_position = 0;                           //terminate change_search_position
      //return GOTO;
    	return SEARCH;
    }
    else{
      // return search_opponent_detected(short_sensor_dist) //check for opp robot
      return SEARCH;
    }
  }

}

/// @brief Function to get the linear for the search task
/// @return linear velocity in m/s
float get_search_linX(){
    return search_linX;
}

/// @brief Function to get the angular velocity for the search task
/// @return angular velocity in deg/s
float get_search_angZ(){
    return search_angZ;
}
