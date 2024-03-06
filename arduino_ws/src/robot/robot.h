#ifndef ROBOT_H
#define ROBOT_H

#include <math.h>
#include "../motors/motors.h"
#include "../sensors/sensors.h"

#define ROBOT_TRACK 0.171674 // [m]

#define ENCODER_FILTER_GAIN 0.5
#define MAGNETO_FILTER_GAIN 0.5

typedef struct {
	float x;
	float y;
	float yaw;
	float linear_velocity;
	float angular_velocity;
} pose;

typedef struct {
    float linear_velocity;
    float angular_velocity;
} twist;

extern pose robot_pose;

#endif // ROBOT_H