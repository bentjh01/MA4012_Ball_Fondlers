#include "../config.h"
// @ShaDowFrost2417
/*
1. Search for the ball e.g. by turning around 
2. Write a check-if-ball-is-detected function to check if ball is detected and differentiate between ball and opponent
*/

int search_task(float x, float y, float yaw, float sensor_A, float sensor_B){
    int success = 0;
    if (success == 1){
        return GOTO_BALL;
    }
    else{
        return 0;
    }
}

int ball_detected(float sensor_A, float sensor_B, float sensor_C, float sensor_D){
    // may need to move this to components into sensors.c
    // Returns 1 if a ball is detected, 0 otherwise
    // return 0 when opponent is detected
    if (sensor_A > BALL_THRESHOLD){
        return 1;
    }
    else if (sensor_B > BALL_THRESHOLD){
        return 1;
    }
    else{
        return 0;
    }
}