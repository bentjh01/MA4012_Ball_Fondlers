#include "main.h"

void init_main(void){
	init_hw();
}

void main_run(void){
	blink_led(1000);
	/*
	if (edge_detected()){
	 	avoid_edge();
	}
	else{
	switch (task_state):
		case SEARCH_TASK:
			search_ball();
		case GO_TO_BALL_TASK:
			goto_ball();
		case COLLECT_BALL_TASK:
			collect_ball();
		case DELIVER_BALL_TASK:
			deliver_ball();
	// this if statement and all computations are to be non-blocking
	 */
}
