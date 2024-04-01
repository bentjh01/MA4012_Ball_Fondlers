#include "../config.h"

// @bentjh01

static float deliver_set_linX;
static float deliver_set_angZ;
static float deliver_set_servo;

void deliver_ball(float yaw, float rpmR, float rpmL, int back_limit_switch) {


    if (fabs(yaw) < DELIVERY_YAW_TOLERANCE) {
        deliver_set_linX = MAX_SPEED;
        deliver_set_angZ = 0;
    }
    else {
        deliver_set_linX = 0;
        deliver_set_angZ = -yaw/fabs(yaw) * MAX_TURN;
    }
    if (back_limit_switch) {
        // Kick Ball out
    }
}

float set_deliiver_linX(){
    return deliver_set_linX;
}

float set_deliiver_angZ(){
    return deliver_set_angZ;
}

float set_deliver_servo(){
    return deliver_set_servo;
}