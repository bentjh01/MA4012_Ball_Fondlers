#include "../config.h"

float deliver_set_linX = 0.0;
float deliver_set_angZ = 0.0;
float deliver_set_servo = SERVO_COLLECT_POSITION;
int reset_robot = NOT_TRIGGERED;

int deliver_task(float yaw, float servo_position, int ball_in_chamber, int back_limit_switch, int lineBL, int lineBR) {
    /// Deliver Task
    /// 1. Inplace rotate to face the back wall at MAX_TURN
    /// 2. Move towards the back wall at MAX_SPEED
    /// 3. Adjust the angular velocity to correct the heading
    /// 4. Wait for the back limit switch to be triggered
    /// 5. Move the arm to the delivery position
    /// 6. Return to the HOME state

    static int delivery_startup;

    // Start the delivery task
    // float deliver_arm_position_err = SERVO_DELIVER_POSITION - servo_position;

    // if (delivery_startup == TRIGGERED){
    //     // Inplace rotate to face the back wall initially
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

    if (fabs(yaw) > YAW_TOLERANCE){
        deliver_set_angZ = -yaw * DELIVER_YAW_KP;
        deliver_set_linX = 0.0;
    }
    else{
        deliver_set_angZ = 0.0;
        deliver_set_linX = -MAX_SPEED;
    }

    // Move the arm to the delivery position
    if (back_limit_switch == TRIGGERED) {
        deliver_set_servo = SERVO_DELIVER_POSITION;
        reset_robot = TRIGGERED;
    }
    
    // CHECK SUCCESS CRITERIA
    if (servo_position == SERVO_DELIVER_POSITION) {
        // reinitialize the task and return to the HOME state
        reset_robot = NOT_TRIGGERED;
        deliver_set_servo = SERVO_COLLECT_POSITION;
        deliver_set_angZ = 0.0;
        deliver_set_linX=0.0;
        return HOME;
    }
    else {
        return DELIVER;
    }
}

float get_reset_robot(){
    return reset_robot;
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