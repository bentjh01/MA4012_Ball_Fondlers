#include "collect_ball.h"
#pragma config(Motor,  port7,           collector,     tmotorServoContinuousRotation, openLoop)

void collect_ball(void){
	// Start Ball Collection
	motor[collector] = 127;
	
	// Check limit switch to see if ball in chamber
	if (limit_switch_chamber == 1){
		motor[collector] = 0;
		task_state = DELIVER_TASK;
	}
	else if (limit_switch_chamber == 0){
		task_state = SEARCH_TASK;
	}
}
