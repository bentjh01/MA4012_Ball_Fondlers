#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include "../config.h"

#define MOTOR_L 0
#define MOTOR_R 1

#define PI 3.14159265

// typedef struct {
// 	float x;
// 	float y;
// 	float yaw;
// 	float linear_velocity;
// 	float angular_velocity;
// } pose;

void robot_move(float linear_velocity, float angular_velocity);

#endif // MOTORS_H
