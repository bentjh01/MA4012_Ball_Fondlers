// PID controller implementation
#include "pid.h"

PIDController pid_init(float Kp, float Ki, float Kd, float setpoint) {
    PIDController pid;
    pid.Kp = Kp;
    pid.Ki = Ki;
    pid.Kd = Kd;
    pid->setpoint = setpoint;
    pid->error_sum = 0.0;
    pid->prev_error = 0.0;
    pid->prev_time = millis()/1000;
    return PIDController;
}

PID pid_update(PIDController pid, float feedback) {
    float dt = millis()/1000 - pid->prev_time;
    float error = pid->setpoint - feedback; 
    pid->error_sum += error * dt;
    float derivative = (error - pid->prev_error) / dt;
    float output = pid->Kp * error + pid->Ki * pid->error_sum + pid->Kd * derivative;
    pid->prev_error = error;
    pid->prev_time = millis()/1000;
    return output;
}

// PIDController deliver = pid_init(1.0, 0.0, 0.0, 0.0, 0.0);

// void loop(){
//     deliver.setpoint = 0.0;
//     deliver = pid_update(deliver, 0.0);
//     output = pid.output;
//     // motor_request(output, output);
// }