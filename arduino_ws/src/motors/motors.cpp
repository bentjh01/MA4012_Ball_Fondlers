#include "motors.h"

int encoder_count_R;
int encoder_count_L;

void motor_request(float rpm_R, float rpm_L);

void robot_move(float linear_velocity, float angular_velocity){
	float radian_per_sec = angular_velocity/180 * PI;
	float rpm_R = (linear_velocity + radian_per_sec*robot_track/2)/(wheel_diameter/2);
	float rpm_L = (linear_velocity - radian_per_sec*robot_track/2)/(wheel_diameter/2);
	motor_request(rpm_R, rpm_L);
}

// Call back function for motor request
void motor_request(float rpm_R, float rpm_L){
  // Set motor speed
  // wheel.rpm_R and wheel.rpm_L
  // motor.setSpeed(MOTOR_R, wheel.rpm_R);
  // motor.setSpeed(MOTOR_L, wheel.rpm_L);
}

// Call back function for motor communication
void motor_callback(void){
  // Read encoder count
  // encoder_count_R = motor.readEncoder(MOTOR_R);
  // encoder_count_L = motor.readEncoder(MOTOR_L);
}
