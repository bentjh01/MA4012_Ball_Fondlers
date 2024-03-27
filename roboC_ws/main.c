
/* _____________________________________________________________________________________________________________________

GLOBAL VARIABLES
_____________________________________________________________________________________________________________________ */

// Robot pose
float robot_x;
float robot_y;
float robot_yaw;
float robot_linX;
float robot_angZ;
float robot_rpmR;
float robot_rpmL;

// robot twist
float robot_cmd_rpmR;
float robot_cmd_rpmL;
float robot_cmd_linX;
float robot_cmd_angZ;

// robot encoders
float robot_enR;
float robot_enL;
float robot_en_rpmR;
float robot_en_rpmL;
float robot_en_linX;
float robot_en_angZ;

// robot magnetometer
float robot_bearing;

// robot line sensors
int robot_line_FL;
int robot_line_BL;
int robot_line_BR;
int robot_line_FR;

// robot task
int task_status;

/* _____________________________________________________________________________________________________________________

TASKS
_____________________________________________________________________________________________________________________ */

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

/* @Unizz20
void wait_for_start(start_button){
	if (start_button == pressed){
		init_robot();
		while(start_button == pressed){
			// wait for button to be released
			task_status = HOME;
		}
}
*/

task main()
{
	init_robot();
	while(1){
		clearTimer(T1);
        read_sensors();
		// main Loop
<<<<<<< HEAD
		if (edge_detected(robot_line_FL, robot_line_BL, robot_line_BR, robot_line_FR)){
			edge_avoid(robot_x, robot_yaw, robot_line_FL, robot_line_FR);
=======
		deivertask(yaw, BL, BR)
		if (edge_detected()){
			edge_avoid(robot_x, robot_yaw, robot_line_FL, robot_line_BL, robot_line_BR, robot_line_FR);
>>>>>>> main
		}
		else{
			switch (task_status){
				case SEARCH{

				}
				.
				.
				.

			}
		}
        // end of main loop
		while (time1[T1] < DT * 1000){}
		update_pose();
	}
}