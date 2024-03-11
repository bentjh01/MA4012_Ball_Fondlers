#include "main.h"

task task_sensors()
{
  while (1)
  {
	read_all_sensors();
  }
}

task main()
{
	startTask(task_sensors);
while (1){
	while (time1[timer_main] < period); // wait for the next period

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
  }
}
