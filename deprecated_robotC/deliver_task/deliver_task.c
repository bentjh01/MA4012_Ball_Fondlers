#include "deliver_task.h"

PIDController delivery_yaw_pid = pid_init(1.0, 0.0, 0.0, DELIVERY_AREA_BEARING);

void deliver_task(void){
  // Check if the robot is at the delivery location
  if (limit_switch_BL && limit_switch_BR){
    // Stop the robot
    robot_move(0, 0);
    // Deliver the package
    // ...
    if (limit_switch_chamber == LOW){
      // The package has been delivered
      task_state = SEARCH_TASK;
    }
  }
  else{
    // Move the robot to the delivery location
    delivery_yaw_pid = pid_update(delivery_yaw_pid, robot_pose.yaw);
    float angular_velocity = delivery_yaw_pid.output;
    robot_move(ALLOWABLE_SPEED(angular_velocity), angular_velocity);
  }
}