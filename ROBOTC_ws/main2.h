#ifndef MAIN2_H
#define MAIN2_H

#include "pinout.h"
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

#define ENCODER_FILTER_GAIN 0.25

#endif // MAIN2_H
