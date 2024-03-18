#ifndef MAIN2_H
#define MAIN2_H

#include "config.h"

typedef struct {
    float linear_x;
    float angular_z;
} twist_t;

typedef struct {
    int left;
    int right;
} motor_rpm_t;

typedef struct {
    float x;
    float y;
    float yaw;
    float linear_x;
    float angular_z;
} pose_t;

typedef struct {
    int left;
    int right;
} encoder_count_t;

typedef struct {
    float Kp;  // Proportional gain
    float Ki;  // Integral gain
    float Kd;  // Derivative gain

    float setpoint;  // Desired setpoint
    float integral; // Accumulated error
    float prev_error; // Previous error
    float prev_time; // Previous time

    float output; // Output
} pid_t;

#endif // MAIN2_H
