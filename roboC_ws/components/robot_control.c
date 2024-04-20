#include "../config.h"

/// @brief Uses a counter to check if enough time steps have passed to complete the desired linear displacement
/// @param linear_displacement 
/// @param linear_speed 
/// @return either SUCCESS if motion is completed or FAIL if motion is not completed
int count_move_forward(float linear_displacement, float linear_speed, float dt){
  static float move_forward_count = 0.0;
  // Startup of the forward movement
  if (move_forward_count >= 0.0){
    // Initialize the count
    move_forward_count = linear_displacement/linear_speed/dt;
    return FAIL;
  }
  // Decrement the count
  move_forward_count --;
  if (move_forward_count <= 0.0){
    return SUCCESS;
  }
  return FAIL;
}

/**
 * Counts the number of rotations needed to reach a desired yaw angle.
 *
 * @param desired_yaw The desired yaw angle in radians.
 * @param yaw The current yaw angle in radians.
 * @param angular_speed The angular speed in radians per second.
 * @param dt The time step in seconds.
 * @return Returns SUCCESS if the desired yaw angle is reached, otherwise returns FAIL.
 */
int count_rotate(float angular_displacement, float yaw, float angular_speed, float dt){
  static float rotate_count = 0.0;
  
  // Startup of the rotation
  if (rotate_count >= 0.0){
    // Initialize the count
    rotate_count = fabs(angular_displacement - yaw)/angular_speed/dt;
    return FAIL;
  }
  
  // Decrement the count
  rotate_count --;
  
  if (rotate_count <= 0.0){
    return SUCCESS;
  }
  
  return FAIL;
}

/// @brief Uses a counter to check if enough time steps have passed to complete the desired rotation
/// @param desired_yaw
/// @param angular_speed 
/// @return either SUCCESS if motion is completed or FAIL if motion is not completed
int robot_rotate(float desired_yaw, float yaw, float angular_speed, float tolerance){
  static float desired_yaw_init;
  if (desired_yaw_init != desired_yaw){
    desired_yaw_init = desired_yaw;
  }

  float angular_displacement = desired_yaw - yaw;
  if (angular_displacement > 180.0){
    angular_displacement -= 360.0;
  }
  else if (angular_displacement < -180.0){
    angular_displacement += 360.0;
  }

  if (fabs(angular_displacement) < tolerance){
    return SUCCESS;
  }
  return FAIL;
}

/**
 * Moves the robot forward by a specified linear displacement and speed.
 *
 * @param x The current x-coordinate of the robot.
 * @param y The current y-coordinate of the robot.
 * @param linear_displacement The desired linear displacement of the robot.
 * @param linear_speed The desired linear speed of the robot.
 * @param tolerance The tolerance for the distance between the current and desired displacement.
 * @return Returns SUCCESS if the robot has reached the desired displacement within the tolerance, otherwise returns FAIL.
 */
int robot_forward(float x, float y, float linear_displacement, float linear_speed, float tolerance){
  static float init_x;
  static float init_y;
  static float init_displacement;
  static float init_speed;
  if (linear_displacement != init_displacement || linear_speed != init_speed){
    init_x = x;
    init_y = y;
    init_displacement = linear_displacement;
    init_speed = linear_speed;
  }
  float displacement = sqrt(pow(x - init_x, 2) + pow(y - init_y, 2));
  float distance = init_displacement - displacement;
  if (distance < tolerance){
    return SUCCESS;
  }
  return FAIL;
}