
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


int edge_detected(){
	if (line_FL_val > LINE_FL){
		return 1;
		} else {
		return 0;
	}
	if (line_BL_val > LINE_BL){
		return 1;
		} else {
		return 0;
	}
	if (line_BR_val > LINE_BR){
		return 1;
		} else {
		return 0;
	}
	if (line_FR_val > LINE_FR){
		return 1;
		} else {
		return 0;
	}
}

int edge_avoid(){
	twist_t twist;
	motor_rpm_t rpm;
	twist.linear_x = 1;
	twist.angular_z = 1;
	calcualte_rpm(twist, rpm);
	calculate_actual_rpm(rpm);
	calculate_actual_twist(rpm, twist);
	robot_move(rpm);
	robot_rpm = rpm;
	robot_twist = twist;
	return 1;
}

int home(){
	int sucess = 0;
	if (sucess == 1){
		return SEARCH_BALL;
	} else {
		return HOME;
	}
}

int search_ball(){
    int sucess = 0;
	if (sucess == 1){
		return GOTO_BALL;
	} else {
		return SEARCH_BALL;
	}
}

int goto_ball(){
    int sucess = 0;
	if (sucess == 1){
		return GRAB_BALL;
	} else {
		return GOTO_BALL;
	}
}

int grab_ball(){
	int sucess = 0;
	if (sucess == 1){
		return DELIVER_BALL;
	} else {
		return GRAB_BALL;
	}
}

int deliver_ball(){
	int sucess = 0;
	if (sucess == 1){
		return HOME;
	} else {
		return DELIVER_BALL;
	}
}

task main()
{
	init_robot();
	while(1){
		clearTimer(T1);
        read_sensors();
		// main Loop
		deivertask(yaw, BL, BR)
		if (edge_detected()){
			edge_avoid(robot_x, robot_yaw, robot_line_FL, robot_line_BL, robot_line_BR, robot_line_FR);
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