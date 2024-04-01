#include "../config.h"

// @bentjh01

static float deliver_pid_integral = 0;
static float deliver_pid_prev_error = 0;

static int BL;
static int BR;
static float rb_yaw;

// float pid_deliver_update(float feedback, float setpointR){
//     float error = setpointR - feedback;
//     deliver_pid_integral = deliver_pid_integral + error * DT;
//     float derivative = (error - deliver_pid_prev_error) / DT;
//     float output = DELIVER_KP * error + DELIVER_KI * deliver_pid_integral + DELIVER_KD * derivative;
//     deliver_pid_prev_error = error;
//     return output;
// }

void deliver_ball(float yaw, float rpmR, float rpmL, int BL, int BR) {
    rb_yaw = yaw;
    BL = BL;
    BR = BR;

    float set_linX;
    float set_angZ;

    if (fabs(yaw) < DELIVERY_YAW_TOLERANCE) {
        set_linX = MAX_SPEED;
        set_angZ = 0;
    }
    else {
        set_linX = 0;
        set_angZ = -yaw/fabs(yaw) * MAX_TURN;
    }
    robot_move_closed(rpmR, rpmL, set_linX, set_angZ);
    if (BL && BR) {
        // Kick Ball out
    }
}


void some_function() {
    float current_yaw = rb_yaw;
}

float deliiver_linX(){
    return set_linX;
}