#include "../config.h"

float deliver_set_linX;
float deliver_set_angZ;
float deliver_set_servo;
int reset_x = NOT_TRIGGERED;

int deliver_task(float yaw, float servo_position, int ball_in_chamber, int back_limit_switch, int lineBL, int lineBR) {
    static int delivery_counter;
    float deliver_arm_position_err = SERVO_DELIVER_POSITION - servo_position;

    if (abs(yaw) > YAW_TOLERANCE){
        deliver_set_angZ = -yaw * DELIVER_YAW_KP;
        deliver_set_linX = 0.0;
    }
    else{
        deliver_set_angZ = 0.0;
        deliver_set_linX = -MAX_SPEED;
    }

    // if (back_limit_switch == TRIGGERED && lineBL == TRIGGERED && lineBR == TRIGGERED) {
    if (back_limit_switch == TRIGGERED) {
        delivery_counter ++;
        deliver_set_servo = SERVO_DELIVER_POSITION;
        reset_x = TRIGGERED;
    }
    
    // CHECK SUCCESS CRITERIA
    // if (ball_in_chamber == NOT_TRIGGERED && delivery_counter > SERVO_POSITION_GAIN) {
    if (delivery_counter > SERVO_POSITION_GAIN) {
        reset_x = TRIGGERED;
        delivery_counter = 0;
        return HOME;
    }
    else if (ball_in_chamber == NOT_TRIGGERED){
        delivery_counter = 0;
        return SEARCH;
    }
    else {
        return DELIVER;
    }
}

float get_reset_x(){
    return reset_x;
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