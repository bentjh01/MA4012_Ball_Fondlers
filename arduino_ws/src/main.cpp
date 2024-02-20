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
	switch (robot_task):
		case 1:
			search_ball();
		case 2:
			goto_ball();
		case 3:
			collect_ball();
		case 4:
			deliver_ball();
	// this if statement and all computations are to be non-blocking
	 */
}
