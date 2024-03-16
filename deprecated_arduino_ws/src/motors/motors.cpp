#include "motors.h"

int encoder_count_R;
int encoder_count_L;

void init_motor(){
  // Set motor pins
  // motor.setPins(MOTOR_R, motor_R_pin1, motor_R_pin2, motor_R_pin3, motor_R_pin4);
  // motor.setPins(MOTOR_L, motor_L_pin1, motor_L_pin2, motor_L_pin3, motor_L_pin4);
  // Set motor speed
  // wheel.rpm_R = 0;
  // wheel.rpm_L = 0;
  // motor.setSpeed(MOTOR_R, wheel.rpm_R);
  // motor.setSpeed(MOTOR_L, wheel.rpm_L);
  // Set motor callback
  // motor.setCallback(MOTOR_R, motor_callback);
  // motor.setCallback(MOTOR_L, motor_callback);
}

void robot_move(float linear_velocity, float angular_velocity){
	float radian_per_sec = angular_velocity/180 * M_PI;
	float rpm_R = (linear_velocity + radian_per_sec*robot_track/2)/(wheel_diameter/2);
	float rpm_L = (linear_velocity - radian_per_sec*robot_track/2)/(wheel_diameter/2);
}