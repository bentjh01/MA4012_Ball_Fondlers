#include "main.h"

int task_state = SEARCH_TASK;

void init_main(void){
	init_hardware();
	pid_init(delivery_yaw_pid, 0.1, 0.0, 0.0, DELIVERY_AREA_DIRECTION);
	Serial.begin(9600);
}

void run_main(void){
	blink_led(1000);
	Serial.println(time_elapsed);
	// if (edge_detected()){
	//  	avoid_edge();
	// }
	// else{
	// switch (task_state):
	// 	case SEARCH_TASK:
	// 		search_ball();
	// 	case GOTO_BALL_TASK:
	// 		goto_ball();
	// 	case COLLECT_BALL_TASK:
	// 		collect_ball();
	// 	case DELIVER_BALL_TASK:
	// }
}

	/*
	switch (robot_task):
		case 1:
			executed_velicty = search_ball_vel();
			executed_ang = search_ball_angl();
		case 2:
			goto_ball(); align with ball
			if (some_condition){
				task_state = 1
			}
			if (short_distance_sensor < X && !opponent){
				task_state = 3
			}
		case 3:
			collect_ball();
			if (some_condition){
				task_state = 1
			}
			if (ball_inchamber){
				task_state = 4
			}

		case 4:
			deliver_ball();
			if (delivered){
				task_state = 1
			}
	send(linX)
	send(angZ)
	// this if statement and all computations are to be non-blocking
	 */
