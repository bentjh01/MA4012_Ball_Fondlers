
void collect_ball(){
	// Start Ball Collection
    // Check if status = collect ball, and, gate is open
	if (task_Status == 4 && limit_3 == 0){
        // Confirm if ball is in front of robot and is not opponent
		if (short_distance_T > 5 and long_distance_M < 7){
                 // Servo move 90 degrees to collect ball
            	robot_servo_move(90);

                // Check if ball in chamber
                if (long_distance_M < -5){
                    // Go to deliver task
                    task_status = 5; 
                }
                
                else{
                    // Open gate
                    robot_servo_moce(-90);

                    // Return back to collect ball
                    task_status = 4;
                }
        }

        
    // Go back to Search + GOTO ball task
	else {
        task_status = 3;
    }
}
