#include "deliver_task.h"

void deliver_task(void){
  // Check if the robot is at the delivery location
  if limit_switch_BL and limit_switch_BR{
    // Stop the robot
    robot_move(0, 0);
    // Deliver the package
    // ...
    task_state = SEARCH_TASK;
  }
  else{
    // Move the robot to the delivery location
    pid_setpoint(delivery_yaw_pid, DELIVERY_AREA_DIRECTION);
    angular_velocity = pid_update(delivery_yaw_pid, robot_pose.yaw);
    robot_move(max_speed, angular_velocity);
  }
}