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

    float output; // Output
} PIDController;

PIDController pid_init(float kp, float ki, float kd, float setpoint);
PIDController pid_update(PIDController pid, float input);

#endif /* PID_H */
