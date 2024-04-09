#include "../config.h"

static float home_linX = 0.0;
static float home_angZ = 0.0;
static float home_servo = 0.0;

int home_task(float x, float y, float yaw, float arm_position){
    home_servo = 0.0;
    home_linX = MAX_SPEED;
    // home_angZ = -1.5 * yaw;
    home_angZ = 0.0;

    if (arm_position > SERVO_TOLERANCE || x < HOME_AWAY_DISTANCE){
        return HOME;
    }
    else{
        home_linX = 0.0;
        home_angZ = 0.0;
        home_servo = 0.0;
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