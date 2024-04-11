#include "../config.h"
#include "components/components.h"

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
static int search_reduce = 0;
static float ball_yaw;
static float search_angular_difference;

//NOTE!!!
//MOVE OPP DETECTION TO
//MAIN CODE GET SENSOR READING IN CM

void search_scan_rotation(float search_initial_yaw, float yaw){
  //start reducing speed after done with half of the 360 degree rotation (180 degree)
  if((fabs(search_initial_yaw)+fabs(yaw)) >= 175.0 && (fabs(search_initial_yaw)+fabs(yaw)) <= 185.00){
    search_reduce = 1;
  }

  if(search_reduce == 0){
    //before 180 degree, rotate ccw constant speed
    search_linX = 0.0;
    search_angZ = 120.0;
  }
  else{
    search_angular_difference = search_initial_yaw-yaw;

    //Calculate angular difference (in vector) for +/- pi range
    if(search_angular_difference <= -180) {
      search_angular_difference = search_angular_difference+360;
    }
    else if (search_angular_difference > 180){
      //technically this should never occur since we always want to rotate ccw. But it is here just in case.
      search_angular_difference = search_angular_difference-360;
    }

    search_linX = 0.0;
    search_angZ = fabs(search_angular_difference)*0.667;

    //limit lowest speed to 30 degrees/s
    if(search_angZ < 30.0){
      search_angZ = 30.0;
    }
  }
  return;
}

int search_task(float x, float y, float yaw, float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float top_sensor_dist, int opp_detected, float search_current_rpmL, float search_current_rpmR){
  //Scanning
  if(changing_search_position == 0){
    //Rotate to scan
    if(search_startup_phase){
    	//reset any movement
    	/*if(fabs(search_current_rpmL) > 0.0001 || fabs(search_current_rpmR) >= 0.0001){
  			search_linX = 0.0;
      	search_angZ = 0.0;
      	return SEARCH;
  		}*/

      //initialization and end startup
      search_startup_phase = 0;
      search_reduce = 0;
      search_initial_yaw = yaw;
      search_counter = 0;
    }

    //check for ball
    if (detect_ball(left_sensor_dist,right_sensor_dist, mid_sensor_dist, top_sensor_dist, opp_detected) == 1){
      //stop movement
      search_linX = 0.0;
      search_angZ = 0.0;
      ball_yaw = yaw;

      search_startup_phase = 1; //reset search_startup_phase
      return GOTO;
    }

    //execute rotation
    search_scan_rotation(search_initial_yaw, yaw);
    search_counter += 1; //increment counter

    //check if 360 deg rotation achieved
    if(fabs(yaw-search_initial_yaw) < YAW_TOLERANCE && search_counter >= SEARCH_COUNT_THRESHOLD){
      //stop movement
      search_linX = 0.0;
      search_angZ = 0.0;

      search_startup_phase = 1;     //reset search_startup_phase
      changing_search_position = 1; //initiate change search position
    }
    return SEARCH;
  }
  else{ //Changing search position == 1
    if(search_startup_phase){
      //reset any movement
    	/*if(fabs(search_current_rpmL) > 0.0001 || fabs(search_current_rpmR) >= 0.0001){
  			search_linX = 0.0;
      	search_angZ = 0.0;
      	return SEARCH;
  		}*/

      //initialization and end startup
      search_startup_phase = 0;
      search_linX = 0.30;
      search_angZ = 0.0;
      search_initial_x = x;
      search_initial_y = y;
    }

    change_position_traveled_distance = sqrt(pow(x-search_initial_x, 2) + pow(y-search_initial_y, 2));

    //check for ball
    if (detect_ball(left_sensor_dist,right_sensor_dist, mid_sensor_dist, top_sensor_dist, opp_detected) == 1){
      //stop movement
      ball_yaw = yaw;
      search_linX = 0.0;
      search_angZ = 0.0;

      search_startup_phase = 1;     //reset search_startup_phase
      changing_search_position = 0; //terminate change_search_position
      return GOTO;
    }

    //check if finished moving to a new search position
    if(change_position_traveled_distance >= CHANGE_POSITION_DISTANCE){
      //stop movement
      search_linX = 0.0;
      search_angZ = 0.0;

      search_startup_phase = 1;                               //reset search_startup_phase
      changing_search_position = 0;                           //terminate change_search_position
    }
    return SEARCH;
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

float get_ball_yaw(){
	return ball_yaw;
}

float search_detectL = 0.0;
float search_detectR = 0.0;
float search_detectM = 0.0;

int move_forward(float cmd_linX, float distance){
  static float move_forward_count = 0.0;
  // Startup of the forward movement
  if (move_forward_count >= 0.0){
    // Initialize the count
    move_forward_count = distance/cmd_linX/DT_MAIN;
    return FAIL;
  }
  // Decrement the count
  move_forward_count --;
  if (move_forward_count <= 0.0){
    return SUCCESS;
  }
  return FAIL;
}

/// @brief Checks if 360 degree rotation is completed
/// @param  cmd_angZ angular velocity command
/// @return the success or failure of the 360 degree rotation
int move_360(float cmd_angZ){
  static float move_360_count = 0.0;
  // Startup of the 360 degree rotation
  if (move_360_count >= 0.0){
    // Initialize the count
    move_360_count = 360.0/abs(cmd_angZ)/DT_MAIN;
    return FAIL;
  }
  // Decrement the count
  move_360_count --;
  if (move_360_count <= 0.0){
    return SUCCESS;
  }
  return FAIL;
}


/// @brief Alternative search task
/// @param ball_detection ball detection status
/// @return the task to be executed
int search_task_alt(float rb_yaw, float left_distance, float right_distance, float mid_distance, float top_distance){
  // 0 for rotate, 1 for move forward
  static int search_state = 0;

  // Check if ball is detected
  search_detectL = detect_ball_left(left_distance);
  search_detectR = detect_ball_right(right_distance);
  search_detectM = detect_ball_mid(mid_distance, top_distance);

  if (detect_back_wall(left_distance, right_distance, mid_distance) == TRIGGERED){
    return SEARCH;
  }
  else if (search_detectL != 0 || search_detectR != 0 || search_detectM != 0){
    // Stop the robot and reinitialise
    ball_yaw = rb_yaw;
    search_state = 0;
    search_linX = 0.0;
    search_angZ = 0.0;
    return GOTO;
  }

  // performs scan ie. rotate and move forward
  if (search_state == 0){
    if (move_360(MAX_TURN) == FAIL){
      search_linX = 0.0;
      search_angZ = MAX_TURN;
    }
    else{
      search_state = 1;
    }
  }
  else{
    if (move_forward(MAX_SPEED, CHANGE_POSITION_DISTANCE) == FAIL){
      search_linX = MAX_SPEED;
      search_angZ = 0.0;
    }
    else{
      search_state = 0;
    }
  }
  return SEARCH;
}
int get_search_detectL(){
  return search_detectL;
}

int get_search_detectR(){
  return search_detectR;
}

int get_search_detectM(){
  return search_detectM;
}