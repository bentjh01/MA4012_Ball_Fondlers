#include "../config.h"

static float home_linX = 0.0;
static float home_angZ = 0.0;
static float home_servo = 0.0;
static int home_startup_phase = 1;
static float home_initial_x = 0;

// Break from HOME when ball is detected. 
// Ignore back sensors for home task

int home_task(float x, float y, float yaw, float arm_position){
    static float home_count = 0.0;
    home_servo = 0.0;
    home_linX = MAX_SPEED;
    // home_angZ = -1.5 * yaw;
    home_angZ = 0.0;
    
    if(home_startup_phase){
    	home_initial_x = x;
    	home_startup_phase = 0;
    }

    // if (arm_position != 0.0 || home_count < HOME_AWAY_DISTANCE/MAX_SPEED/DT_MAIN){
    if (arm_position != 0.0 || x - home_initial_x < HOME_AWAY_DISTANCE){
        home_count ++;
        return HOME;
    }
    else{
        home_count = 0.0;
        home_linX = 0.0;
        home_angZ = 0.0;
        home_servo = 0.0;
        home_startup_phase = 1;
        return SEARCH;
    }
}

/// @brief Fetches the command linear velocity of the robot
/// @return linear velocity [m/s]
float get_home_linX(){
    return home_linX;
}

/// @brief Fetches the command angular velocity of the robot
/// @return angular velocity [deg/s]
float get_home_angZ(){
    return home_angZ;
}

float get_home_servo(){
    return home_servo;
}