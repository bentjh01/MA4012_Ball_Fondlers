#include "main.h"

// #include "deliver_task/deliver_task.h"
#include "blink_led/blink_led.h"
#include "touch_sensor/touch_sensor.h"

task task_sensors() 
{
	while (1)
	{
		read_touch_sensor();
		// read_all_sensors();
	}
}

task main()
{
	startTask(task_sensors);
	init_led()
	while (1){
		while (time1[timer_main] < PERIOD){}; // wait for the next period
		increment_counter();
		blinky();

		// if (edge_detected()){
		// 	avoid_edge();
		// }
		// else{
		// 	switch (task_state){
		// 	case SEARCH_TASK:
		// 		search_ball();
		// 	case GOTO_BALL_TASK:
		// 		//goto_ball();
		// 	case COLLECT_BALL_TASK:
		// 		//collect_ball();
		// 	case DELIVER_BALL_TASK:
		// 		//deliver_ball();
		// 	}
		// }
	}
}
