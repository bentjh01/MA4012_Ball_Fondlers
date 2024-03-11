#include "collect_ball.h"

void collect_ball(void){
	// Check if Short Distance Sensor is less than or equal 11cm, and Long distance sensor don't detect opponent
	if (short_dist <= 11cm and long_distA >= 20){
		// Move robot backward 5cm
		robot_move(,);
		
		// Move collector arm up to desired position
		servo.move(80degrees);
		
		// Move robot forward 10cm
		robot_move(,);
		
		// Start Ball Collection
		// Rotate Servo 100 degrees to capture ball
		servo_move(-100degrees);
		
		// Check limit switch to see if ball in chamber
		if (limit_switch_chamber == LOW){
			task_state = DELIVER_TASK;
		}
		else if (limit_switch_chamber == HIGH){
			task_state = SEARCH_TASK;
		}
	}
	
	else{
		// Continue Searching for ball
	}
