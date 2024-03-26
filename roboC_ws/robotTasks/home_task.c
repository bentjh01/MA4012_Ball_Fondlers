#include "../config.h"

// @Unizz20

/*
1. Opens the claw to collect the ball
2. Moves to middle of the field
sucess == claw_opened && middle_of_field
*/

int home_task(float x, float y, float yaw, float sensor_A, float sensor_B){
    int success = 0;
    if (success == 1){
        return SEARCH_BALL;
    }
    else{
        return HOME;
    }
}