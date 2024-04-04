#include "collect_ball.h"
#pragma config(Motor,  port7,           collector,     tmotorServoContinuousRotation, openLoop)

task collect_ball(){
	// Start Ball Collection
	motor[collector] = 50;
	
	// Check limit switch to see if ball in chamber
	if (limit_switch_chamber == 1){
		motor[collector] = 0;
		task_state = DELIVER_TASK;
	}
	else if (limit_switch_chamber == 0){
		motor[collector] = 0;
		task_state = SEARCH_TASK;
	}
}
