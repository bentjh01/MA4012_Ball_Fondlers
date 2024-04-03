#include "../config.h"

static float deliver_set_linX;
static float deliver_set_angZ;
static float deliver_set_servo;

int deliver_task(float yaw, float servo_position, int ball_in_chamber, int back_limit_switch) {
    float deliver_arm_position_err = SERVO_DELIVER_POSITION - servo_position;

    if (fabs(yaw) > YAW_TOLERANCE) {
        deliver_set_linX = 0;
        deliver_set_angZ = -1.0 * sgn(yaw) * MAX_TURN;
    }
    else {
        deliver_set_linX = MAX_SPEED;
        deliver_set_angZ = 0;
    }

    if (back_limit_switch) {
        deliver_set_servo = SERVO_DELIVER_POSITION;
    }

    if (fabs(deliver_arm_position_err) < SERVO_TOLERANCE && ball_in_chamber == NOT_TRIGGERED) {
        return HOME;
    }
    else if (ball_in_chamber == NOT_TRIGGERED){
        return SEARCH;
    }
    else {
        return DELIVER;
    }
}

float get_deliver_linX(){
    return deliver_set_linX;
}

float get_deliver_angZ(){
    return deliver_set_angZ;
}

float get_deliver_servo(){
    return deliver_set_servo;
}