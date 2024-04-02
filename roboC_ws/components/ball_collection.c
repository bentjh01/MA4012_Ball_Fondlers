
void collect_ball(){
	// Start Ball Collection
    // Check if status = collection, and, gate is open
	if (task_Status == 4 && limit_3 == 0){
		if (short_dist_sensor > 5 and long_dist_sensor_mid < 7){
            		robot_servo_move;
        }

        // Check if ball in the chamber
        if (short_dist < 0){
            // Go to deliver task
            task_status = 5; 
        }

    // Go back to Search + GOTO ball task
	else {task_status = 3}
}
