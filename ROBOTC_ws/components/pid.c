// PID controller implementation
#include "pid.h"

void pid_init(PIDController* pid, double Kp, double Ki, double Kd, double setpoint) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->setpoint = setpoint;
    pid->integral = 0.0;
    pid->prev_error = 0.0;
}

double pid_update(PIDController* pid, double input, double dt) {
    double error = pid->setpoint - input;
    pid->integral += error * dt;
    double derivative = (error - pid->prev_error) / dt;
    double output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;
    pid->prev_error = error;
    return output;
}
