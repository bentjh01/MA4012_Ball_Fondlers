#include "../config.h"

static float home_linX = 0.0;
static float home_angZ = 0.0;
static float home_servo = 0.0;

int home_task(float x, float y, float yaw, float arm_position, float sensor_mid, float sensor_top, float sensor_left, float sensor_right){
    static int home_startup = 1;
    static int home_initial_x = 0.0;
    static float home_count = 0.0;
    home_servo = 0.0;
    home_linX = MAX_SPEED;
    home_angZ = -yaw;
    home_angZ = 0.0;
    
    if(home_startup == 1){
        home_count = 0.0;
        home_linX = 0.0;
        home_angZ = 0.0;
        home_servo = 0.0;
        
    	home_initial_x = x;
    	home_startup = 0;
    }

    if (home_count >= HOME_TIMEOUT){
        home_startup = 1;
        return SEARCH;
    }
    else if (arm_position == 0.0 && x - home_initial_x >= HOME_AWAY_DISTANCE){
        home_startup = 1;
        return SEARCH;
    }
    else{
        home_count ++;
        return HOME;
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