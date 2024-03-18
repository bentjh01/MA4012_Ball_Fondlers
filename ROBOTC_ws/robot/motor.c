#include "robot.h"

void robot_move(float linear_velocity, float angular_velocity){
	float radian_per_sec = angular_velocity/180 * M_PI;
	float rpm_R = (linear_velocity + radian_per_sec*robot_track/2)/(wheel_diameter/2);
	float rpm_L = (linear_velocity - radian_per_sec*robot_track/2)/(wheel_diameter/2);
}