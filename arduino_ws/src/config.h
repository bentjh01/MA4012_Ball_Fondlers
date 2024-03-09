#ifndef CONFIG_H
#define CONFIG_H

#include <math.h>
#include <Arduino.h>
#include <Wire.h>

// TUNABLE PARAMETERS

// May need to add for each individual sensor
#define LINE_SENSOR_THRESHOLD 512

// Direction of delivery area
#define DELIVERY_AREA_DIRECTION 50 // [degrees]

// PID controller parameters
// pid_init(delivery_yaw_pid, 1.0, 0.0, 0.0, DELIVERY_AREA_DIRECTION);

// GLOBAL VARIABLES
extern int task_state;
extern int dt;


// CONSTANTS
constexpr int period = 20;
constexpr float max_speed = 1.0; //m/s
constexpr float wheel_diameter = 0.05; //m
constexpr float robot_track = 0.3; //m

#endif // CONFIG_H