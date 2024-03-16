#include "robot.h"

float fast_inverse_sqrt(float x) {
  // Union allows reinterpreting bits as a float
  union {
    float f;
    long i;
  } conv;

  // Initial guess using bit shift and bias adjustment
  conv.f = x;
  conv.i = 0x5f3759df - (conv.i >> 1);

  // One iteration of Newton-Raphson method for refinement
  conv.f = conv.f * (1.5f - (x * conv.f * conv.f));

  // Return the refined value
  return conv.f;
}

float discretise_yaw(float yaw){
    if (0 < yaw){
        if (yaw < 22.5){
            return NORTH;
        }
        else if (22.5<= yaw < 3*22.5){
            return NORTH_WEST;
        }
        else if (3*22.5<= yaw < 5*22.5){
            return WEST;
        }
        else if (5*22.5<= yaw < 7*22.5){
            return SOUTH_WEST;
        }
        else (7*22.5< yaw){
            return SOUTH;
        }
    }
    else{
        if (yaw > -22.5){
            return NORTH;
        }
        else if (-22.5 >= yaw > -3*22.5){
            return NORTH_EAST;
        }
        else if (-3*22.5 >= yaw > -5*22.5){
            return EAST;
        }
        else if (-5*22.5 >= yaw > -7*22.5){
            return SOUTH_EAST;
        }
        else (-7*22.5 > yaw){
            return SOUTH;
        }
    }
}
  

/**
 * @brief State Space Model of robot. 
 * @param last_pose Current pose of the robot
 * @param dt Time step
 * @return predicted current pose of the robot
*/
void predict_state_model(pose last_pose, twist last_cmd_vel, float dt) {
    pose estimated_pose;
    estimated_pose.x = last_pose.x + last_pose.linear_velocity * dt * cos(last_pose.yaw);
    estimated_pose.y = last_pose.y + last_pose.linear_velocity * dt * sin(last_pose.yaw);
    estimated_pose.yaw = last_pose.yaw + last_pose.angular_velocity * dt;
    estimated_pose.linear_velocity = cmd_vel.linear_velocity;
    estimated_pose.angular_velocity = cmd_vel.angular_velocity;
    return estimated_pose;
}

void predict_state_encoders(pose last_pose, encoder_count new_en_count, encoder_count old_en_count, float dt) {
    pose estimated_pose;
    int d_encoder_right = new_en_count.right - old_en_count.right;
    int d_encoder_left = new_en_count.left - old_en_count.left;
    // Simple robot model
    float dx = (d_encoder_right + d_encoder_left) * ENCODER_RESOLUTION / 2 * cos(state->theta);
    float dy = (d_encoder_right + d_encoder_left) * ENCODER_RESOLUTION / 2 * sin(state->theta);
    float dyaw = (d_encoder_right - d_encoder_left) * ENCODER_RESOLUTION / ROBOT_TRACK;

    estimated_pose.x = last_pose.x + dx;
    estimated_pose.y = last_pose.y + dy;
    estimated_pose.yaw = last_pose.yaw + dyaw;
    estimated_pose.linear_velocity = fast_inverse_sqrt(dx**2 + dy**2) / dt;
    estimated_pose.angular_velocity = dyaw / dt;
    return estimated_pose;
}

void predict_state_magnetometer(pose pose, float magnetometer_yaw){
    pose estimated_pose;
    // float d_magnetometer_yaw = new_magnetometer_yaw - last_magnetometer_yaw;
    estimated_pose.yaw = magnetometer_yaw;
    return estimated_pose;
}

float kalman_filter_update(pose robot_pose, twist last_cmd_vel, encoder_count new_en_count, encoder_count old_en_count, float magnetometer_yaw, float dt){
    pose predicted_pose = predict_state(robot_pose, last_cmd_vel, dt);
    pose encoder_pose = predict_state_encoders(robot_pose, new_en_count, old_en_count, dt);
    pose magnetometer_pose = predict_state_encoders(robot_pose, magnetometer_yaw);

    float encoder_x_innovation = encoder_pose.x - predicted_pose.x;
    float encoder_y_innovation = encoder_pose.y - predicted_pose.y;
    float encoder_yaw_innovation = encoder_pose.yaw - predicted_pose.yaw;
    float encoder_linear_velocity_innovation = encoder_pose.linear_velocity - predicted_pose.linear_velocity;
    float encoder_angular_velocity_innovation = encoder_pose.angular_velocity - predicted_pose.angular_velocity;

    float magnetometer_yaw_innovation = magnetometer_pose.yaw - discretise_yaw(predicted_pose.yaw);

    robot_pose.x = predicted_pose.x + ENCODER_FILTER_GAIN * encoder_x_innovation;
    robot_pose.y = predicted_pose.y + ENCODER_FILTER_GAIN * encoder_y_innovation;
    robot_pose.yaw = predicted_pose.yaw + ENCODER_FILTER_GAIN * encoder_yaw_innovation + MAGNETO_FILTER_GAIN * magnetometer_yaw_innovation;
    robot_pose.linear_velocity = predicted_pose.linear_velocity + ENCODER_FILTER_GAIN * encoder_linear_velocity_innovation;
    robot_pose.angular_velocity = predicted_pose.angular_velocity + ENCODER_FILTER_GAIN * encoder_angular_velocity_innovation;

    return robot_pose;
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


