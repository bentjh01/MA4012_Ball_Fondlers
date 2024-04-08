// #pragma config(Sensor, dgtl1,  Reset_Start_Switch, sensorDigitalIn)
// #pragma config(Motor,  port6,           motor_R,       tmotorVex393_MC29, PIDControl, encoderPort, dgtl4)
// #pragma config(Motor,  port7,           motor_L,       tmotorVex393_MC29, PIDControl, reversed, encoderPort, dgtl2)


// void init_robot(void){
// 	robot_x = 0;
//   robot_y = 0;
//   robot_yaw = 0;
//   robot_linX = 0;
//   robot_angZ = 0;
//   robot_rpmR = 0;
//   robot_rpmL = 0;
//   resetMotorEncoder(motor_R);
// resetMotorEncoder(motor_L);
// return;
// }

// void center_start(){
// 	motor[motor_R] = 127;
// 	motor[motor_L] = 127;
// 	delay(500);
// 	motor[motor_R] = 0;
// 	motor[motor_L] = 0;
// }

// void reset_start()
// {
// 	while(true){
// 		if(SensorValue(Reset_Start_Switch) == 1){
// 			init_robot(); 	// Initialise Robot
// 			center_start();	// Move robot to center of arena and start searching
// 			task = SEARCH_TASK;
// 		}
// 	}
// }
