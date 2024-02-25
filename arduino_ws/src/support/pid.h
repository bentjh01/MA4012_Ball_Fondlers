#ifndef PID_H
#define PID_H

#include <Arduino.h>

typedef struct {
    float Kp;  // Proportional gain
    float Ki;  // Integral gain
    float Kd;  // Derivative gain

    float setpoint;  // Desired setpoint
    float error_sum; // Accumulated error
    float prev_error; // Previous error
    float prev_time; // Previous time
} PIDController;

void pid_init(PIDController* pid, float kp, float ki, float kd, float setpoint);
void pid_setpoint(PIDController* pid, float setpoint);
float pid_update(PIDController* pid, float input);


#endif /* PID_H */
