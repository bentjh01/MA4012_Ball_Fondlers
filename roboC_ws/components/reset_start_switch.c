void init_robot(void){
	robot_x = 0;
    robot_y = 0;
    robot_yaw = 0;
    robot_linX = 0;
    robot_angZ = 0;
    robot_rpmR = 0;
    robot_rpmL = 0;
    resetMotorEncoder(motor_R);
	resetMotorEncoder(motor_L);
}

// Move to center of arena
void move_to_center(){
	if (robot_x < 120){ // arena length/2 = 2.4m/2
		robot_move_closed(127, 0);
	}
	else{
		robot_move_closed(0,0);
		int center_state = 1; // Robot reached the center of arena
	}
}
	
void center_start(){
	// Begin Search upon reaching the center
	if (center_state == 1){
		task_status = 2; // Search status
	}
	else {
		move_to_center();
	}
}

void reset_start()
{
	while(true){
		if(SensorValue(Reset_Start_Switch) == 0){
			// Initialise all conditions of the robot
			init_robot();
			task_status = 0; // Home status
			
			if (SensorValue(Reset_Start_Switch) == 1){
				// Move robot to center of arena
				move_to_center();
				
				// Start Search
				center_start();			
		}
	}
}

