#include "main.h"

#include "tasks/tasks.h"
#include "robot/robot.h"

int test;
pose robot_pose;

task main(){
	while (true){
		test = touch_test_task();
		wait1Msec(100);
	}
}
