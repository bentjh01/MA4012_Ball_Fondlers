#include "differential_drive_model.h"

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

motor control(twist cmd_vel){
	robot_wheel wheel;
	wheel.rpm_R = (cmd_vel.linear_velocity + cmd_vel.angular_velocity*track/2)/(wheel_diameter/2);
	wheel.rpm_L = (cmd_vel.linear_velocity - cmd_vel.angular_velocity*track/2)/(wheel_diameter/2);
	return wheel;
}

pose forward_kinematics(pose initial_pose, twist cmd_vel, float dt){
	pose final_pose;
	final_pose.x = initial_pose.x + cos(initial_pose.yaw) * cmd_vel.linear_velocity * dt;
	final_pose.y = initial_pose.y + sin(initial_pose.yaw) * cmd_vel.linear_velocity * dt;
	final_pose.yaw = initial_pose.yaw + cmd_vel.angular_velocity * dt;
	final_pose.linear_velocity = cmd_vel.linear_velocity;
	final_pose.angular_velocity = cmd_vel.linear_velocity;
	return final_pose;
}
