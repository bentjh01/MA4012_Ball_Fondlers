#include "../config.h"

float deliver_set_linX = 0.0;
float deliver_set_angZ = 0.0;
float deliver_set_servo = SERVO_COLLECT_POSITION;
int reset_x = NOT_TRIGGERED;

/// @brief Uses a counter to check if enough time steps have passed to complete the desired linear displacement
/// @return either SUCCESS if motion is completed or FAIL if motion is not completed
int count_move_del(float linear_displacement, float angular_displacement, float linear_speed, float angular_speed){
    static int move_dep = 0;
  static float depmove_forward_count = 0.0;
  static float depmove_angular_count = 0.0;
  // Startup of the forward movement
//   if (depmove_forward_count >= 0.0 || depmove_angular_count >= 0.0){
    if (move_dep ==0){
    // Initialize the count
    depmove_forward_count = linear_displacement/linear_speed/DT_MAIN;
    depmove_angular_count = angular_displacement/angular_speed/DT_MAIN;
    move_dep = 1;
    return FAIL;
  }
  // Decrement the count
  depmove_forward_count --;
  depmove_angular_count --;
  if (depmove_forward_count <= 0.0 && depmove_angular_count <= 0.0){
    move_dep=0;
    return SUCCESS;
  }
  return FAIL;
}

int deliver_task(float rb_x, float yaw, float servo_position, int ball_in_chamber, int back_limit_switch, int lineBL, int lineBR) {
    static int delivery_startup = TRIGGERED;
    static int delivery_wait;
    static int avd_opponent = 0;

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
    if (back_limit_switch == TRIGGERED && fabs(yaw) < YAW_TOLERANCE && lineBL == TRIGGERED && lineBR ==TRIGGERED) {
        deliver_set_servo = SERVO_DELIVER_POSITION;
        reset_x = TRIGGERED;
    }
    else if (back_limit_switch == TRIGGERED && rb_x > ARENA_X/8.0){
        avd_opponent = 1;
    }

    if (avd_opponent == 1){
        if (count_move_del(0.1, 45.0, MAX_SPEED/2.0, MAX_TURN/4.0) == FAIL){
            deliver_set_linX = MAX_SPEED/2.0;
            deliver_set_angZ = MAX_TURN/2.0;
            return DELIVER;
        }
        else{
            avd_opponent = 0;
        }
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

