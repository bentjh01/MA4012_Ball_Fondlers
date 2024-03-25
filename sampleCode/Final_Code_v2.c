#pragma config(Sensor, in3,    Sharp_Back,     sensorAnalog)
#pragma config(Sensor, in2,    Sharp_Top_Front, sensorAnalog)
#pragma config(Sensor, in1,    Sharp_Right,    sensorAnalog)
#pragma config(Sensor, in4,    IR_Right_Back,  sensorAnalog)
#pragma config(Sensor, in5,    IR_Right_Front, sensorAnalog)
#pragma config(Sensor, in6,    IR_Left_Back,   sensorAnalog)
#pragma config(Sensor, in7,    IR_Left_Front,  sensorAnalog)
#pragma config(Sensor, in8,    Sharp_Left,     sensorAnalog)
#pragma config(Sensor, dgtl1,  on_switch,      sensorTouch)
#pragma config(Sensor, dgtl2,  switch_right,   sensorTouch)
#pragma config(Sensor, dgtl3,  right_encoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ball_switch,    sensorTouch)
#pragma config(Sensor, dgtl6,  switch_left,    sensorTouch)
#pragma config(Sensor, dgtl7,  left_encoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  compass1,       sensorDigitalIn)
#pragma config(Sensor, dgtl10, compass2,       sensorDigitalIn)
#pragma config(Sensor, dgtl11, compass3,       sensorDigitalIn)
#pragma config(Sensor, dgtl12, compass4,       sensorDigitalIn)
#pragma config(Motor,  port2,           rightmotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           collector,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           gatemotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           leftmotor,     tmotorServoContinuousRotation, openLoop, reversed)

int Motor_On_Time;
int Time_1cm = 45;
int Time_1Degree =31;
int Left_Sharpsensor_Dist;
int Right_Sharpsensor_Dist;
//int distance_to_ball_left_sensor;
//int distance_to_ball_right_sensor;
int state;
int collecting;
int prev_state;
int Start_switch;
//int T3_clear;
int time_2;

int F_L_Sensor;
//int Front_Left_IRLine;
int F_R_Sensor;
//int Front_Right_IRLine;
int B_L_Sensor;
//int Back_Left_IRLine;
int B_R_Sensor;
//int Back_Right_IRLine;

//int debug_left_search;
//int debug_right_search;
//int debug_state2;

//int distance_to_ball;

int Debug_Sharp_Sensor_Back;
int Debug_Sharp_Sensor_Top_Front;
int Debug_Sharp_Sensor_Right;
int Debug_Sharp_Sensor_Left;

//float time_to_the_centre;

//int result_left;
//int result_right;

int left_sensor_found = 0;
int right_sensor_found = 0;

int time_1;
//int time_2;
//int time_left_search;
//int time_right_search;

//int need_to_stop;

int ball_found;

int beginning;

int time_clear = 0;

int boundary_sensors = 0;
int near_boundary = 0;

int detected_opponent = 0;
int searching_case = 1;

int searching_direction = 1;

int start_checking = 0;

void move_forward(int dist){
	Motor_On_Time = dist*Time_1cm ;
	motor[leftmotor] = 127;
	motor[rightmotor] = 127;
	delay(Motor_On_Time);
	motor[leftmotor] = 0;
	motor[rightmotor] = 0;
}

void move_forward_infinite(){
	motor[leftmotor] = 127;
	motor[rightmotor] = 127;
}

void move_backward_infinite(){
	motor[leftmotor] = -127;
	motor[rightmotor] = -127;
}

void turn_left(int degree){
	Motor_On_Time = degree*Time_1Degree;
	motor[leftmotor] = -24;
	motor[rightmotor] = 24;
	delay(Motor_On_Time);
	motor[leftmotor] = 0 ;
	motor[rightmotor] = 0 ;
}
void turn_left_infinite(){
	motor[leftmotor] = -24;
	motor[rightmotor] = 24;
}

void stop_motors(){
	motor[leftmotor] = 0;
	motor[rightmotor] = 0;
}

void turn_right(int degree){
	Motor_On_Time = degree*Time_1Degree;
	motor[leftmotor] = 24;
	motor[rightmotor] = -24;
	delay(Motor_On_Time);
	motor[leftmotor] = 0 ;
	motor[rightmotor] = 0 ;
}

void turn_right_infinite(){
	motor[leftmotor] = 24;
	motor[rightmotor] = -24;
}

int left_sensor(){
	Left_Sharpsensor_Dist = SensorValue(Sharp_Left);
	if (Left_Sharpsensor_Dist >= 1500 /* rewrite 100 with the correct value for 100cm */){
		return Left_Sharpsensor_Dist;
	}
	else{
		return 1;
	}
}

int right_sensor(){
	Right_Sharpsensor_Dist = SensorValue(Sharp_Right); /* Rewrite 100 with the resolution of each sharp sensor analog value */
	if (Right_Sharpsensor_Dist >= 1500 /* rewrite 100 with the correct value for 100cm */){
		return Right_Sharpsensor_Dist;
	}
	else{
		return 1;
	}
}

void move_backward(int dist) {
	Motor_On_Time = dist * Time_1cm;
	motor[leftmotor] = -127;
	motor[rightmotor] = -127;
	delay(Motor_On_Time);
	motor[leftmotor] = 0;
	motor[rightmotor] = 0;
}

void turn_right_indef(){
	motor[leftmotor] = 24;
	motor[rightmotor] = -24;
}

int Front_Left_IRSensor(){
	F_L_Sensor = SensorValue(IR_Left_Front);
	if (F_L_Sensor <= 400){
		return 1;
	}
	else{
		return 0;
	}
}

int Front_Right_IRSensor(){
	F_R_Sensor = SensorValue(IR_Right_Front);
	if (F_R_Sensor <= 400){
		return 1;
	}
	else{
		return 0;
	}
}

int Back_Left_IRSensor(){
	B_L_Sensor = SensorValue(IR_Left_Back);
	if (F_L_Sensor <= 400){
		return 1;
	}
	else{
		return 0;
	}
}

int Back_Right_IRSensor(){
	B_R_Sensor = SensorValue(IR_Right_Back);
	if (B_R_Sensor <= 400){
		return 1;
	}
	else{
		return 0;
	}
}

int back_sensor(){
	int Back_Sharpsensor_Dist = SensorValue(Sharp_Back); /* Rewrite 100 with the resolution of each sharp sensor analog value */
	if (Back_Sharpsensor_Dist >= 2000 /* rewrite 100 with the correct value for 100cm */){
		return 1;
	}
	else{
		return 0;
	}
}

int front_sensor(){
	int Front_Sharpsensor_Dist = SensorValue(Sharp_Top_Front); /* Rewrite 100 with the resolution of each sharp sensor analog value */
	if (Front_Sharpsensor_Dist >= 2000 /* rewrite 100 with the correct value for 100cm */){
		return 1;
	}
	else{
		return 0;
	}
}

int check_boundary(){
	boundary_sensors = Back_Right_IRSensor() + 2*Back_Left_IRSensor() + 4*Front_Right_IRSensor() + 8*Front_Left_IRSensor();
	return boundary_sensors;
	//Read sensors
	//Set boundary_sensors to combination code of infra sensors that detect yellow line
	//FL, FR, BL, BR
	//return boundary_sensors
}

int check_opponent(){
	int back_sensor_detect = back_sensor();
	int front_sensor_detect = front_sensor();
	if (back_sensor_detect){
		detected_opponent = 1;
	}
	else if (front_sensor_detect){
		detected_opponent = 2;
	}
	else if (front_sensor_detect && back_sensor_detect){
		detected_opponent = 3;
	}
	else{
		detected_opponent = 0;
	}
	return detected_opponent;
}

int read_compass()
{
    int pin1 = SensorValue(compass1);
    int pin2 = SensorValue(compass2);
    int pin3 = SensorValue(compass3);
    int pin4 = SensorValue(compass4);
    int combination = pin1 * 1000 + pin2 * 100 + pin3 * 10 + pin4;
//@Darrens, before, north east, east, and south east all return 3
    switch (combination)
    {
    case 1101:
        //compass_status = NORTH;
        return(1);
    case 1001:
        //compass_status = NORTH_EAST;
        return(7);
    case 1011:
        //compass_status = EAST;
        return(2);
    case 0011:
        //compass_status = SOUTH_EAST;
        return(8);
    case 0111:
        //compass_status = SOUTH;
        return(4);
    case 0110:
        //compass_status = SOUTH_WEST;
        return(5);
    case 1110:
        //compass_status = WEST;
        return(3);
    case 1100:
        //compass_status = NORTH_WEST;
        return(6);
    default:
        //compass_status = INVALID_COMBINATION;
        return(0);    }
}

void find_foward_direction(){
	while (true){
		int dir = read_compass();
		if(dir==1){
			stop_motors();
			break;
		}
		else{
			turn_left_infinite();
		}
	}
}

void find_backward_direction(){
	while (true){
		int dir = read_compass();
		if(dir==4){
			stop_motors();
			break;
		}
		else{
			turn_left_infinite();
		}
	}
}

void find_left_direction(){
	while (true){
		int dir = read_compass();
		if(dir==3){
			stop_motors();
			break;
		}
		else{
			turn_left_infinite();
		}
	}
}

void find_right_direction(){
	while (true){
		int dir = read_compass();
		if(dir==2){
			stop_motors();
			break;
		}
		else{
			turn_right_infinite();
		}
	}
}

void FL_FR_Avoid() {
  int current_dir = read_compass();
  switch (current_dir) {
  case 1: //North
    find_left_direction(); searching_direction = 3; break;
  case 2: //East
    find_foward_direction(); searching_direction = 1; break;
  case 3: //West
    find_backward_direction(); searching_direction = 4; break;
  case 4: //South
    find_right_direction(); searching_direction = 2; break;
  case 5: //South West
    find_backward_direction(); searching_direction = 4; break;
  case 6: //North West
    find_left_direction(); searching_direction = 3; break;
  case 7: //North East
    find_foward_direction(); searching_direction = 1; break;
  case 8: //South East
    find_right_direction(); searching_direction = 2; break;
  default:
    find_foward_direction();searching_direction = 1;  break;
  }
}

void FL_Avoid() {
  int current_dir = read_compass();
  switch (current_dir) {
  case 1: //North
    find_right_direction(); searching_direction = 2; break;
  case 2: //East
    find_backward_direction(); searching_direction = 4; break;
  case 3: //West
    find_foward_direction(); searching_direction = 1; break;
  case 4: //South
    find_left_direction(); searching_direction = 3; break;
  case 5: //South West
    find_left_direction(); searching_direction = 3; break;
  case 6: //North West
    find_foward_direction(); searching_direction = 1; break;
  case 7: //North East
    find_right_direction(); searching_direction = 2; break;
  case 8: //South East
    find_backward_direction(); searching_direction = 4; break;
  default:
    find_foward_direction();searching_direction = 1;  break;
  }
}

void FR_Avoid() {
  int current_dir = read_compass();
  switch (current_dir) {
  case 1: //North
    find_left_direction(); searching_direction = 3; break;
  case 2: //East
    find_foward_direction(); searching_direction = 1; break;
  case 3: //West
    find_backward_direction(); searching_direction = 4; break;
  case 4: //South
    find_right_direction(); searching_direction = 2; break;
  case 5: //South West
    find_backward_direction(); searching_direction = 4; break;
  case 6: //North West
    find_left_direction(); searching_direction = 3; break;
  case 7: //North East
    find_foward_direction(); searching_direction = 1; break;
  case 8: //South East
    find_right_direction(); searching_direction = 2; break;
  default:
    find_foward_direction();searching_direction = 1;  break;
  }
}

void BL_BR_Avoid() {
  int current_dir = read_compass();
  switch (current_dir) {
  case 1: //North
    find_foward_direction(); searching_direction = 1; break;
  case 2: //East
    find_foward_direction(); searching_direction = 1; break;
  case 3: //West
    find_foward_direction(); searching_direction = 1; break;
  case 4: //South
    find_backward_direction(); searching_direction = 4; break;
  case 5: //South West
    find_backward_direction(); searching_direction = 4; break;
  case 6: //North West
    find_foward_direction(); searching_direction = 1; break;
  case 7: //North East
    find_foward_direction(); searching_direction = 1; break;
  case 8: //South East
    find_backward_direction(); searching_direction = 4; break;
  default:
    find_foward_direction(); searching_direction = 1; break;
  }
}

void Left_Avoid() {
  int current_dir = read_compass();
  switch (current_dir) {
  case 1: //North
    find_right_direction(); searching_direction = 2; break;
  case 2: //East
    find_backward_direction(); searching_direction = 4; break;
  case 3: //West
    find_foward_direction(); searching_direction = 1; break;
  case 4: //South
    find_left_direction(); searching_direction = 3; break;
  case 5: //South West
    find_left_direction(); searching_direction = 3; break;
  case 6: //North West
    find_foward_direction(); searching_direction = 1; break;
  case 7: //North East
    find_right_direction(); searching_direction = 2; break;
  case 8: //South East
    find_backward_direction(); searching_direction = 4; break;
  default:
    find_foward_direction(); searching_direction = 1; break;
  }
}

void Right_Avoid() {
  int current_dir = read_compass();
  switch (current_dir) {
  case 1: //North
    find_left_direction(); searching_direction = 3; break;
  case 2: //East
    find_foward_direction();searching_direction = 1;  break;
  case 3: //West
    find_backward_direction(); searching_direction = 4; break;
  case 4: //South
    find_right_direction(); searching_direction = 2; break;
  case 5: //South West
    find_backward_direction(); searching_direction = 4; break;
  case 6: //North West
    find_left_direction(); searching_direction = 3; break;
  case 7: //North East
    find_foward_direction(); searching_direction = 1; break;
  case 8: //South East
    find_right_direction(); searching_direction = 2; break;
  default:
    find_foward_direction(); searching_direction = 1; break;
  }
}



void deposit_ball(){
	if (SensorValue(ball_switch) == 1){
    motor[gatemotor] = -30;
    delay(500);
    motor[gatemotor] = 0;
    delay(500);
    motor[gatemotor] = 30;
    delay(900);
    motor[gatemotor] = 0;
   }
}



void collect_state(){
		if (check_boundary()>0){
				prev_state = 2;
				state = 4;
		}
		if (check_opponent()>0){
				prev_state = 2;
				state = 5;
		}
	  if (collecting==1){
	  	clearTimer(T4);
	  	motor[collector]=127;
		  move_forward_infinite();
	  }
	  if (SensorValue[ball_switch]==1){
		  stop_motors();
		  motor[collector]=0;
		  collecting = 0;
      ball_found = 1;
		  prev_state = 2;
		  state = 3;
	  }
	  else {
			collecting = 0;
			move_forward_infinite();
			int time_4 = time1[T4];
			if (time_4 > 20000){
				stop_motors();
				motor[collector]=-127;
				wait1Msec(1000);
				motor[collector]=0;
				ball_found = 0;
				state = 1;
				collecting = 1;
			}
			else{
				motor[collector] = 127;
			}
	  }
}

void move_forward_checking(int dist){
	while(1){
		if (start_checking == 0){
			clearTimer(T2);
			motor[leftmotor] = 127;
			motor[rightmotor] = 127;
			start_checking = 1;
		}
		time_2 = time1[T2];
		if (time_2 >= (dist * Time_1cm)){
			stop_motors();
			start_checking = 0;
			break;
		}
		if (check_boundary()>0){
				stop_motors();
				start_checking = 0;
				prev_state = 1;
				state = 4;
				break;
		}
		if (check_opponent()>0){
				stop_motors();
				start_checking = 0;
				prev_state = 1;
				state = 5;
				break;
		}
	}
}

void left_search(){
	//ROTATE TO THE LEFT UNTIL THE BALL IS FOUND (WITHIN LIMIT)
	for (int count_deg = 1; count_deg < 80; count_deg++){
		if (check_boundary()>0){
				prev_state = 1;
				state = 4;
				break;
		}
		if (check_opponent()>0){
				prev_state = 1;
				state = 5;
				break;
		}
		if (left_sensor() == 1){	//If the ball is not found, keep rotating until 90 deg
			turn_left(1);
		}
		//BALL FOUND WHILE ROTATING LEFT BY THE LEFT SENSOR
		else if (left_sensor() != 1){
			if (time_clear != 1){
				clearTimer(T1);
				time_clear = 1;
			}
			//ROTATE TO THE LEFT UNTIL RIGHT SENSOR DETECT
			if (right_sensor() == 1){
				turn_left(1);
			}
		  //if right sensor detect, get the current time and distance to the ball by right sensor, and rotate to the centre
			else if (right_sensor() != 1){
				int time_1 = time1[T1];
				float time_to_the_centre = ((time_1)/2);
                turn_right_infinite();
                wait1Msec(time_to_the_centre);
                stop_motors();
                time_clear = 0;
			}
			state = 2;
			collecting = 1;
			ball_found = 1;
         	break;
        }
	}
}


void right_search(){
	for (int count_deg = 1; count_deg < 100; count_deg++){   //Search right 90deg
		if (check_opponent()>0){
				prev_state = 1;
				state = 5;
				break;
		}
		if (check_boundary()>0){
				prev_state = 1;
				state = 4;
				break;
		}
		if (right_sensor() == 1){	//If the ball is not found, keep rotating until 90 deg
			turn_right(1);
		}
		else if (right_sensor() != 1){  //Ball is found by right sensor
			if (time_clear != 1){
				clearTimer(T1);
				time_clear = 1;
			}
			if (left_sensor() == 1){ //Turn right until left sensor detect
				turn_right(1);
			}
			else if (left_sensor() != 1){ //Ball is found by left sensor
		     //if right sensor detect, get the current time and distance to the ball by right sensor, and rotate to the centre
				time_1 = time1[T1];
				float time_to_the_centre = ((time_1)/2);
      	        turn_left_infinite();
             	wait1Msec(time_to_the_centre);  //Go the the centre
             	stop_motors();
            	time_clear = 0;
			}
            state = 2;
            collecting = 1;
			ball_found = 1;
            break;
        }
	}
}

void searching_state(){
    if (beginning == 0){
        move_forward(75);
        beginning = 1;
    }
    else {
        if (ball_found == 0){ //Ball not found
            left_search();
						if (state==1){
            /*if (ball_found == 1){

                stop_motors();
                state = 3;
                prev_state = 1;
            }*/
            	if (ball_found == 0){ //Ball not found
                		right_search();
                /*if (near_boundary == 1){
                    stop_motors();
                    state = 4;
                    prev_state = 1;
                }
				else if (opponent_during_searching == 1){
					stop_motors();
					state = 5;
					prev_state = 1;
				}*/
                /*if (ball_found == 1){
                    stop_motors();
                    state = 3;
                    prev_state = 1;
                }*/
					if (state==1){
                		if (ball_found == 0){ //Ball still not found
                           /* if (searching_case == 1) {find_foward_direction();}
                            else if (searching_case == 2) {find_foward_direction();}
                            else if (searching_case == 3) {find_foward_direction();}
                            else if (searching_case == 4) {find_foward_direction();}
                            else if (searching_case == 5) {find_left_direction();}
                            else if (searching_case == 6) {find_left_direction();}
                            else if (searching_case == 7) {find_left_direction();}
                            else if (searching_case == 8) {find_left_direction();}
                            else if (searching_case == 9) {find_backward_direction();}
                            else if (searching_case == 10) {find_backward_direction();}
                            else if (searching_case == 11) {find_backward_direction();}
                            else if (searching_case == 12) {find_backward_direction();}
                            else if (searching_case == 13) {find_right_direction();}
                            else if (searching_case == 14) {find_right_direction();}
                            else if (searching_case == 15) {find_right_direction();}
                            else if (searching_case == 16) {find_right_direction(); searching_case = 0;}
                    		//find_foward_direction();  //Rotate back to centre
                            searching_case = searching_case + 1;*/
                    				switch(searching_direction){
                    					case 1: find_foward_direction(); break;
                    					case 2: find_right_direction(); break;
                    					case 3: find_left_direction(); break;
                    					case 4: find_backward_direction(); break;
                    				}
                            move_forward_checking(25);
                    /*if (near_boundary == 1){
                        stop_motors();
                        state = 4;
                        prev_state = 1;
                    }
					else if (opponent_during_searching == 1){
						stop_motors();
						state = 5;
						prev_state = 1;
					}*/
                		}
					}
            	}
			}
        }
    }
}


void return_state(){
	int dir = read_compass();
	if(dir==1){
        /*if (check_boundary() != 0){
            state = 4;
            prev_state = 3;
        }
		if (check_opponent()>0){
			state = 5;
			prev_state = 3;
		}*/
		if ((SensorValue(switch_left)==1)&&(SensorValue(switch_right)==1)){
			motor[leftmotor]=0;
			motor[rightmotor]=0;
			motor[collector] = -127;
			deposit_ball();
			prev_state = 3;
			beginning = 0;
			ball_found = 0;
            searching_case = 1;
			state = 1;
			wait1Msec(1000);
			motor[collector] = 0;
		}
		else{
			move_backward(25);
		}
	}
	else{
		turn_right_indef();
	}
}

void avoid_boundary_state(){
  switch (boundary_sensors){
    case 1: //BR detect
      move_forward(25);
      BL_BR_Avoid();
      state = prev_state;
      break;
    case 2: //BL detect
      move_forward(25);
      BL_BR_Avoid();
      state = prev_state;
      break;
    case 3: //BACK: BL & BR detect
      move_forward(25);
      BL_BR_Avoid();
      state = prev_state;
      break;
    case 4: //FR detect
      move_backward(25);
          //turn_left(45);
      FR_Avoid();
      state = prev_state;
      break;
    case 5: //RIGHT: BR & FR detect
      //turn_left(90);
      //move_forward(25);
      Right_Avoid();
      state = prev_state;
      break;
      //turn_right(45);
    case 8: //FL detect
      move_backward(25);
          //turn_right(45);
      FL_Avoid();
      state = prev_state;
      break;
    case 10: //LEFT: FL & BL detect
      //turn_right(90);
      move_forward(25);
      Left_Avoid();
      state = prev_state;
      break;
      //turn_left(45);
    case 12: //FRONT: FL & FR detect
      move_backward(25);
      FL_FR_Avoid();
      state = prev_state;
      //ball_found = 0;
      break;
    default: state = 3;
  }
  //find_forward_direction();
    near_boundary = 0;
}

void avoid_opp_state(){
	switch(detected_opponent){
		case 1: //Detect back sensor
			move_forward(30);
			//if(check_boundary()>0){
				//prev_state = 5;
				//state = 4;
				//return 1;
			//}
			turn_left(90);
			//if(check_boundary()>0){
				//prev_state = 5;
			//	state = 4;
				//return 1;
			//}
			move_forward(30);
			//if(check_boundary()>0){
				//prev_state = 5;
				//state = 4;
				//return 1;
			//}
			turn_right(90);
			//if(check_boundary()>0){
			//	prev_state = 5;
			//	state = 4;
				//return 1;
			//}
			state = prev_state;
			break;
		case 2: //Detect front sensor
			move_backward(30);
			//if(check_boundary()>0){
				//prev_state = 5;
				//state = 4;
				//return 1;
			//}
			turn_left(90);
			//if(check_boundary()>0){
				//prev_state = 5;
				//state = 4;
				//return 1;
			//}
			move_backward(30);
			//if(check_boundary()>0){
				//prev_state = 5;
				//state = 4;
				//return 1;
			//}
			turn_right(90);
			//if(check_boundary()>0){
				//prev_state = 5;
				//state = 4;
				//return 1;
			//}
			state = prev_state;
			break;
		case 3: //Detect both sensors
			turn_left(90);
			//if(check_boundary()>0){
				//prev_state = 5;
			//	state = 4;
				//return 1;
			//}
			move_forward(30);
			//if(check_boundary()>0){
				//prev_state = 5;
				//state = 4;
				//return 1;
			//}
			turn_right(90);
			//if(check_boundary()>0){
				//prev_state = 5;
				//state = 4;
				//return 1;
			//}
			state = prev_state;
			break;
		default: state = 3;
	}
	//opponent_during_searching = 0;
	state = prev_state;
}

task main(){
	//state: 1(Searching), 2(Collect), 3(Return), 4(Avoid Boundary), 5(Avoid Opponent)
	left_sensor_found = 0;
	right_sensor_found = 0;
	state = 1;
	while(true){
		Debug_Sharp_Sensor_Back = SensorValue(Sharp_Back) ;
		Debug_Sharp_Sensor_Top_Front = SensorValue(Sharp_Top_Front);
		Debug_Sharp_Sensor_Right = SensorValue(Sharp_Right);
		Debug_Sharp_Sensor_Left = SensorValue(Sharp_Left);
		Start_switch = SensorValue(on_switch);
		if (SensorValue(on_switch) == 1){
			break;
		}
	}
	clearTimer(T3);
	searching_direction = 1; //1 Forward, 2 Right, 3 Left, 4 Backward
	while(1){
		/*if ((SensorValue(switch_left)!=1)&&(SensorValue(switch_right)!=1)){
			if (check_boundary() > 0){
				//prev_state = state;
				//ball_found = 0;
				//state = 4;
			}
			if (check_opponent() > 0){
				prev_state = state;
				ball_found = 0;
				state = 5;
			}
		}*/
		switch(state){
	 		case 1: searching_state(); break;
			case 2: collect_state(); break;
	 		case 3: return_state(); break;
	 		case 4: avoid_boundary_state(); break;
	 		case 5: avoid_opp_state(); break;
	 		default: return_state();
	 	}
	}
}
