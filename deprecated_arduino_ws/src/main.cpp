#include "main.h"

int task_state = SEARCH_TASK;
unsigned long last_time = millis();

void init_main(void){
	init_hardware();
	init_controllers();
}

void run_main(void){
	// Tasks to run unlimited
	read_all_sensors();
	dt = millis() - last_time;
	if (dt >= period){
		if (edge_detected()){
			avoid_edge();
		}
		else{
			switch (task_state){
				case SEARCH_TASK:
					search_ball();
				case GOTO_BALL_TASK:
					goto_ball();
				case COLLECT_BALL_TASK:
					collect_ball();
				case DELIVER_BALL_TASK:
					deliver_ball();
			}
		}
		// send(linX)
		// send(angZ)
		last_time = millis();
	}
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