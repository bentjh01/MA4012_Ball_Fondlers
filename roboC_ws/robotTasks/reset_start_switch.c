
// static float reset_start_linX = 0.0;
// static float reset_start_angZ = 0.0;
// static float reset_start_servo = 0.0;

// // Move to center of arena
// int move_to_center(){
// 	if (robot_x < 1.2){ // arena length/2 = 2.4m/2
// 		reset_start_linX = MAX_SPEED;
// 		reset_start_angZ = 0;
// 		reset_start_servo = SERVO_HOME_POSITION;
// 	}
// 	else{
// 		reset_start_linX = 0;
// 		reset_start_angZ = 0;
// 		reset_start_servo = SERVO_HOME_POSITION;
// 		int center_state = 1; // Robot reached the center of arena
// 	}
// }
	
// int center_start(){
// 	// Begin Search upon reaching the center
// 	if (center_state == 1){
// 		return SEARCH;
// 	}
// 	else {
// 		move_to_center();
// 	}
// }

// void reset_start()
// {
// 	if(SensorValue(Reset_Start_Switch) == 0){
// 		// Initialise all conditions of the robot
// 		init_robot();
// 		return HOME;
		
// 		if (SensorValue(Reset_Start_Switch) == 1){
// 			// Move robot to center of arena
// 			move_to_center();
			
// 			// Start Search
// 			center_start();			
// 		}
// 	}
// }



// float get_collect_linX(){
//     return reset_start_linX;
// }

// float get_collect_angZ(){
//     return reset_start_angZ;
// }

// float get_collect_servo(){
//     return reset_start_servo;
// }

