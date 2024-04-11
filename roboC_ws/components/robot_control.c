#include "../config.h"

/// @brief Uses a counter to check if enough time steps have passed to complete the desired linear displacement
/// @param linear_displacement 
/// @param linear_speed 
/// @return either SUCCESS if motion is completed or FAIL if motion is not completed
int count_move_forward(float linear_displacement, float linear_speed){
  static float move_forward_count = 0.0;
  // Startup of the forward movement
  if (move_forward_count >= 0.0){
    // Initialize the count
    move_forward_count = linear_displacement/linear_speed/DT_MAIN;
    return FAIL;
  }
  // Decrement the count
  move_forward_count --;
  if (move_forward_count <= 0.0){
    return SUCCESS;
  }
  return FAIL;
}

/// @brief Uses a counter to check if enough time steps have passed to complete the desired rotation
/// @param angular_displacement 
/// @param angular_speed 
/// @return either SUCCESS if motion is completed or FAIL if motion is not completed
int count_move_rotate(float angular_displacement, float angular_speed){
  static int count_move_rotate_init = 1;
  static float move_rotate_count = 0;
  // Startup of the 360 degree rotation
  if (count_move_rotate_init == 1){
    move_rotate_count = angular_displacement/fabs(angular_speed)/DT_MAIN;
    count_move_rotate_init = 0.0;
  }
  // Decrement the count
  move_rotate_count --;
  if (move_rotate_count <= 0.0){
    count_move_rotate_init = 1;
    return SUCCESS;
  }
  return FAIL;
}