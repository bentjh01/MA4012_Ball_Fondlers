#include "../config.h"

float deliver_pid_integral = 0;
float deliver_pid_prev_error = 0;

int BL;
int BR;
float rb_yaw;

// PID Controller for the right motor
float pid_deliver_update(float feedback, float setpointR){
    float error = setpointR - feedback;
    deliver_pid_integral = deliver_pid_integral + error * DT;
    float derivative = (error - deliver_pid_prev_error) / DT;
    float output = DELIVER_KP * error + DELIVER_KI * deliver_pid_integral + DELIVER_KD * derivative;
    deliver_pid_prev_error = error;
    return output;
}

void deliver_ball(float yaw, int BL, int BR) {
    rb_yaw = yaw;
    BL = BL;
    BR = BR;

    float set_linX = 0.0;
    float set_angZ = pid_deliver_update(yaw, 0.0);
    if (fabs(yaw) < DELIVERY_YAW_TOLERANCE) {
        set_linX = MAX_SPEED;
    }
}


void some_function() {
    float current_yaw = rb_yaw;
}