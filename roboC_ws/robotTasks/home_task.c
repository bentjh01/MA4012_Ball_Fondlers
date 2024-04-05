#include "../config.h"

// @Unizz20

/*
1. Opens the claw to collect the ball
2. Moves to middle of the field
sucess == claw_opened && middle_of_field
*/

static float home_linX = 0.0;
static float home_angZ = 0.0;
static float home_servo = 0.0;

int home_task(float x, float y, float yaw, float sensor_A, float sensor_B){
    int success = 0;
    if (success == 1){
        return SEARCH;
    }
    else{
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