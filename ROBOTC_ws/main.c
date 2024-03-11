task task1()
{
  while (1)
  {
  	wait1Msec(1000);
  }
}

task main()
{
	startTask(task1);
while (1){
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
}
