#include "../config.h"

float deliver_set_linX = 0.0;
float deliver_set_angZ = 0.0;
float deliver_set_servo = SERVO_COLLECT_POSITION;
int reset_x = NOT_TRIGGERED;

int deliver_task(float yaw, float servo_position, int ball_in_chamber, int back_limit_switch, int lineBL, int lineBR) {
    static int delivery_startup = TRIGGERED;
    static int delivery_wait;

    /// Reset the delivery task
    if (delivery_startup == TRIGGERED){
        delivery_wait = DELIVERY_WAIT;
        delivery_startup = NOT_TRIGGERED;
    }

    if (fabs(yaw) > YAW_TOLERANCE){
        // deliver_set_angZ = -sgn(yaw) * DELIVER_YAW_KP;
        deliver_set_angZ = -sgn(yaw) * MAX_TURN;
        deliver_set_linX = 0.0;
    }
    else{
        deliver_set_linX = -MAX_SPEED;
        deliver_set_angZ = -yaw * DELIVER_YAW_KP;
    }

    // Move the arm to the delivery position
    if (back_limit_switch == TRIGGERED) {
        deliver_set_servo = SERVO_DELIVER_POSITION;
        reset_x = TRIGGERED;
    }
    
    // CHECK SUCCESS CRITERIA
    if (servo_position == SERVO_DELIVER_POSITION) {
        delivery_wait --;
        if (delivery_wait <= 0){
            delivery_startup = TRIGGERED;
            reset_x = NOT_TRIGGERED;
            deliver_set_servo = SERVO_COLLECT_POSITION;
            deliver_set_angZ = 0.0;
            deliver_set_linX=0.0;
            return HOME;
        }
    }
    return DELIVER;
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