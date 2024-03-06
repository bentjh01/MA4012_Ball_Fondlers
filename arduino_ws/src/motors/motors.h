#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include "../config.h"

#define MOTOR_L 0
#define MOTOR_R 1

#define PI 3.14159265
#define ENCODER_RESOLUTION 4 // [deg]

// make function that resets the count of the encoders
typedef struct{
	int right;
	int left;
} encoder_count;

void robot_move(float linear_velocity, float angular_velocity);

#endif // MOTORS_H
