#include "edge_detection.h"

//Line_Sensor define in sensor.h
//  line_sensor_FL = HIGH/LOW
//  line_sensor_BL = HIGH/LOW
//  line_sensor_BR = HIGH/LOW
//  line_sensor_FR = HIGH/LOW

//Some functions about move, rotate and stop
void move_forward(int dist){
	Motor_On_Time = dist * Time_1cm ;
	motor[leftmotor] = 127;
	motor[rightmotor] = 127;
	delay(Motor_On_Time);
	motor[leftmotor] = 0;
	motor[rightmotor] = 0;
}

void move_backward(int dist){
	Motor_On_Time = dist * Time_1cm ;
	motor[leftmotor] = -127;
	motor[rightmotor] = -127;
	delay(Motor_On_Time);
	motor[leftmotor] = 0;
	motor[rightmotor] = 0;
}

void turn_left(int degree){
	Motor_On_Time = degree * Time_1Degree;
	motor[leftmotor] = -24;
	motor[rightmotor] = 24;
	delay(Motor_On_Time);
	motor[leftmotor] = 0 ;
	motor[rightmotor] = 0 ;
}

void turn_right(int degree){
	Motor_On_Time = degree * Time_1Degree;
	motor[leftmotor] = 24;
	motor[rightmotor] = -24;
	delay(Motor_On_Time);
	motor[leftmotor] = 0 ;
	motor[rightmotor] = 0 ;
}

void stop_motors(){
	motor[leftmotor] = 0;
	motor[rightmotor] = 0;
}

bool edge_detected(){
//Check FL sensor detect state
    if (line_sensor_FL == HIGH) {
        FL_value = 1;
    } else {
        FL_value = 0;}
//Check FR sensor detect state
    if (line_sensor_FR == HIGH) {
        FR_value = 1;
    } else {
        FR_value = 0;}
//Check BL sensor detect state
    if (line_sensor_BL == HIGH) {
        BL_value = 1;
    } else {
        BL_value = 0;}
//Check BR sensor detect state
    if (line_sensor_BR == HIGH) {
        BR_value = 1;
    } else {
        BR_value = 0;}

Edge_detected_value =  FL_value * 1 + FR_value * 2 + BL_value * 4 + BL_value * 8;
//The value of Edge_detected_value can be 0-16, Corresponding to the 16 possible detect results of 4 IR sensors

//Use Edge_avoid_enabled to determine whether we need take "Avoid Edge" action;
//For Edge_detected_value= 0..., robot is safe;
//For Edge_detected_value=..., we should take Avoid edge action;
    if (Edge_detected_value == 0) {
        return 0;
    } else {
        return 1;}
}

void avoid_edge(){
//Run when Edge_avoid_enabled == true.
//When detect the edge and should take actions, stop first
    stop_motors();
    wait1Msec(500);
//Then Control the robot to perform different motions based on the different detect results
//the value and grouping are fake now, need further discuss about how to group
//    if (Edge_detected_value == 1 || Edge_detected_value == 3 ) {
//       avoid_edge_motion = 1;
//    } else if (Edge_detected_value == 4 || Edge_detected_value == 6) {
//        avoid_edge_motion = 2;
//    } else {
//       avoid_edge_motion = 3;
//    }
//This actions are not comprehensive, may need ball collect stutas, detect status and compass to further breakdown
    switch (Edge_detected_value):
		case 1://FL
			FL_avoid();
		case 2://FR
			
		case 3://FL+FR
			
		case 4://BL
			
        case 5://FL+BL

        case 8://BR

        case 10://FR+BR

        case 12://BL+BR

}
// NORTH 0
// NORTH_EAST 1
// EAST 2
// SOUTH_EAST 3
// SOUTH 4
// SOUTH_WEST 5
// WEST 6
// NORTH_WEST 7
// INVALID -1

void FL_avoid(){
    int current_dir = compass_bearing
    switch (current_dir) {
        case 0: //North
            
        case 1: //North East
            
        case 2: //East
            
        case 3: //South East
            
        case 4: //South
            
        case 5: //South West
            
        case 6: //West
            
        case 7: //North West
            
    }
}
