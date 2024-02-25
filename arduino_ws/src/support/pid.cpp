// PID controller implementation
#include "pid.h"

void pid_init(PIDController* pid, float Kp, float Ki, float Kd, float setpoint) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->setpoint = setpoint;
    pid->error_sum = 0.0;
    pid->prev_error = 0.0;
    pid->prev_time = millis()/1000;
}

float pid_update(PIDController* pid, float input) {
    float dt = millis()/1000 - pid->prev_time;
    float error = pid->setpoint - input;
    pid->error_sum += error * dt;
    float derivative = (error - pid->prev_error) / dt;
    float output = pid->Kp * error + pid->Ki * pid->error_sum + pid->Kd * derivative;
    pid->prev_error = error;
    pid->prev_time = millis()/1000;
    return output;
}

void pid_setpoint(PIDController* pid, float setpoint) {
    pid->setpoint = setpoint;
}
