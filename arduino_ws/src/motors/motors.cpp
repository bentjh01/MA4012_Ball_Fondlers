#include "motors.h"

void robot_move(float linear_velocity, float angular_velocity){
	float radian_per_sec = angular_velocity/180 * PI
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
  // 
}

/*
 * Kinematics of Differential Drive Robots
 * w * (R + b/2) = v_R
 * w * (R - b/2) = v_L
 * w = Angular Velocity
 * R = Distance from Instantaneous Centre of Rotation
 * b = track
 * v_R and v_L = tangential velocity of wheels
*/

/* Robot Model - Differntial Drive 
 * This code is to perform forward and backward kinematics of the robot
 * Control Signals = Linear and Angular Velocities
 *
 */



// pose forward_kinematics(pose initial_pose, twist cmd_vel, float dt){
// 	pose final_pose;
// 	final_pose.x = initial_pose.x + cos(initial_pose.yaw) * cmd_vel.linear_velocity * dt;
// 	final_pose.y = initial_pose.y + sin(initial_pose.yaw) * cmd_vel.linear_velocity * dt;
// 	final_pose.yaw = initial_pose.yaw + cmd_vel.angular_velocity * dt;
// 	final_pose.linear_velocity = cmd_vel.linear_velocity;
// 	final_pose.angular_velocity = cmd_vel.linear_velocity;
// 	return final_pose;
// }
