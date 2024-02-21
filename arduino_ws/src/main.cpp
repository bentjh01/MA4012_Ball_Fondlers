#include "main.h"

void init_main(void){
	init_hw();
}

void main_run(void){
	blink_led(1000);
void main_run(void){
	blink_led(1000);
	/*
	if (edge_detected()){
	 	avoid_edge();
	}
	else{
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
}
