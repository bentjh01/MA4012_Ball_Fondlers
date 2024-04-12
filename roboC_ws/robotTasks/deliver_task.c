#include "../config.h"

float deliver_set_linX = 0.0;
float deliver_set_angZ = 0.0;
float deliver_set_servo = SERVO_COLLECT_POSITION;
int reset_x = NOT_TRIGGERED;

int deliver_task(float yaw, float servo_position, int ball_in_chamber, int back_limit_switch, int lineBL, int lineBR) {
    static int delivery_startup;

    // float deliver_arm_position_err = SERVO_DELIVER_POSITION - servo_position;

    // // Start the delivery task
    // if (delivery_startup == TRIGGERED){
    //     // Face the back wall
    //     // deliver_set_angZ = -yaw * DELIVER_YAW_KP;
    //     deliver_set_angZ = -sgn(yaw) * MAX_TURN;
    //     deliver_set_linX = 0.0;
    //         if (abs(yaw) < YAW_TOLERANCE){
    //             delivery_startup = NOT_TRIGGERED;
    //         }
    // }
    // else {
    //     // Move towards the back wall while making small corrections
    //     deliver_set_angZ = -yaw * DELIVER_YAW_KP;
    //     deliver_set_linX = -MAX_SPEED;
    // }

    // // Correcting the error when trasition -180
    // if (deliver_arm_position_err <= -180.0){
    //     deliver_arm_position_err += 360.0;
    // }
    // else if (deliver_arm_position_err > 180.0){
    //     deliver_arm_position_err -= 360.0;
    // }

    if (fabs(yaw) > YAW_TOLERANCE){
        deliver_set_angZ = -yaw * DELIVER_YAW_KP;
        deliver_set_linX = 0.0;
    }
    else{
        deliver_set_linX = -MAX_SPEED;
        deliver_set_angZ = 0.0;
    }

    // Move the arm to the delivery position
    if (back_limit_switch == TRIGGERED) {
        deliver_set_servo = SERVO_DELIVER_POSITION;
        reset_x = TRIGGERED;
    }
    
    // CHECK SUCCESS CRITERIA
    if (servo_position == SERVO_DELIVER_POSITION) {
        reset_x = TRIGGERED;
        deliver_set_servo = SERVO_COLLECT_POSITION;
        deliver_set_angZ = 0.0;
        deliver_set_linX=0.0;
        return HOME;
    }
    // else if (ball_in_chamber == NOT_TRIGGERED){
    //     return SEARCH;
    // }
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