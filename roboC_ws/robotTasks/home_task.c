#include "../config.h"

static float home_linX = 0.0;
static float home_angZ = 0.0;
static float home_servo = 0.0;

int home_task(float x, float y, float yaw, float arm_position, float distanceL, float distanceR, float distanceM, float distanceT){
    home_servo = 0.0;
    home_linX = MAX_SPEED;
    home_angZ = -1.5 * yaw;

    float detect_L = detect_ball_left(distanceL, LIMIT_DISTANCE_READINGS);
    float detect_R = detect_ball_right(distanceR, LIMIT_DISTANCE_READINGS);
    float detect_M = detect_ball_mid(distanceM, distanceT, LIMIT_DISTANCE_READINGS);

    // if (detect_back_wall(distanceL, distanceR, distanceM) == NOT_TRIGGERED){
    //     if (detect_L > 0.0 || detect_R > 0.0 || detect_M > 0.0){
    //         home_linX = 0.0;
    //         home_angZ = 0.0;
    //         home_servo = 0.0;
    //         return SEARCH;
    //     }
    // }

    if (arm_position != 0.0 || x < HOME_AWAY_DISTANCE){
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