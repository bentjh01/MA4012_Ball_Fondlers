#include <math.h>
#include "../config.h"
#define PI 3.14159265

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

typedef struct {
	float rpm_R;
	float rpm_L;
} robot_wheel;
