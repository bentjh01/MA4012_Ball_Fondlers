#include "edge_detect+avoid.h"
#include "motors.h"
#include <windows.h>//In order to use sleep() function

//Line_Sensor define in sensor.h
//  line_sensor_FL = HIGH/LOW
//  line_sensor_BL = HIGH/LOW
//  line_sensor_BR = HIGH/LOW
//  line_sensor_FR = HIGH/LOW

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
//For Edge_detected_value=..., we should take Avoid_edge action;
    if (Edge_detected_value == 0) {
        return 0;
    } else {
        return 1;}
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

void find_north_direction(){
	while (true){
		int dir = compass_bearing;
		if(dir==0){
			robot_move(0, 0);;
			break;
		}
		else{
			if(dir==1 || dir==2 || dir==3 || dir==4){
				//turn left
                robot_move(0, 20);
			}
			else{
				//turn right
                robot_move(0, -20);
			}
		}
	}
}

void find_south_direction(){
	while (true){
		int dir = compass_bearing;
		if(dir==4){
			robot_move(0, 0);;
			break;
		}
		else{
			if(dir==5 || dir==6 || dir==7 || dir==0){
				robot_move(0, 20);
			}
			else{
				robot_move(0, -20);
			}
		}
	}
}

void find_east_direction(){
	while (true){
		int dir = compass_bearing;
		if(dir==42){
			robot_move(0, 0);;
			break;
		}
		else{
			if(dir==3 || dir==4 || dir==75 || dir==6){
				robot_move(0, 20);
			}
			else{
				robot_move(0, -20);
			}
		}
	}
}

void find_west_direction(){
	while (true){
		int dir = compass_bearing;
		if(dir==6){
			robot_move(0, 0);
			break;
		}
		else{
			if(dir==7 || dir==0 || dir==1 || dir==2){
				robot_move(0, 20);
			}
			else{
				robot_move(0, -20);
			}
		}
	}
}

void FL_avoid(){
    int current_dir = compass_bearing;
    switch (current_dir)
        case 0: //North
            find_south_direction()
        case 1: //North East
            find_south_direction()
        case 2: //East
            find_west_direction()
        case 3: //South East
            find_west_direction()
        case 4: //South
            find_north_direction()
        case 5: //South West
            find_north_direction()
        case 6: //West
            find_east_direction()
        case 7: //North West
            find_east_direction()
    }

void FR_avoid(){
    int current_dir = compass_bearing;
    switch (current_dir)
        case 0: //North
            find_south_direction()
        case 1: //North East
            find_west_direction()
        case 2: //East
            find_west_direction()
        case 3: //South East
            find_north_direction()
        case 4: //South
            find_north_direction()
        case 5: //South West
            find_east_direction()
        case 6: //West
            find_east_direction()
        case 7: //North West
}

void FL_FR_avoid(){
    int current_dir = compass_bearing;
    switch (current_dir) 
        case 0: //North
            //
        case 1: //North East
            //
        case 2: //East
            
        case 3: //South East
            
        case 4: //South
            
        case 5: //South West
            
        case 6: //West
            
        case 7: //North West
            
}

void BL_avoid(){
    int current_dir = compass_bearing;
    switch (current_dir) 
        case 0: //North
            //
        case 1: //North East
            //
        case 2: //East
            
        case 3: //South East
            
        case 4: //South
            
        case 5: //South West
            
        case 6: //West
            
        case 7: //North West
}
void BR_avoid(){
    int current_dir = compass_bearing;
    switch (current_dir) 
        case 0: //North
            //
        case 1: //North East
            //
        case 2: //East
            
        case 3: //South East
            
        case 4: //South
            
        case 5: //South West
            
        case 6: //West
            
        case 7: //North West
}
void BL_BR_avoid(){
    int current_dir = compass_bearing;
    switch (current_dir) 
        case 0: //North
            //
        case 1: //North East
            //
        case 2: //East
            
        case 3: //South East
            
        case 4: //South
            
        case 5: //South West
            
        case 6: //West
            
        case 7: //North West
}
void FL_BL_avoid(){
    int current_dir = compass_bearing;
    switch (current_dir) 
        case 0: //North
            //
        case 1: //North East
            //
        case 2: //East
            
        case 3: //South East
            
        case 4: //South
            
        case 5: //South West
            
        case 6: //West
            
        case 7: //North West
}
void FR_BR_avoid(){
    int current_dir = compass_bearing;
    switch (current_dir) {
        case 0: //North
            //
        case 1: //North East
            //
        case 2: //East
            
        case 3: //South East
            
        case 4: //South
            
        case 5: //South West
            
        case 6: //West
            
        case 7: //North West
}
}

void avoid_edge(){
//Run when Edge_avoid_enabled == true.
//When detect the edge and should take actions, stop the motor first
    robot_move(0, 0);
    delay(500);

    switch (Edge_detected_value):
		case 1://FL
            robot_move(-1, 0)//move backward
            delay(500)
			FL_avoid();
		case 2://FR
            robot_move(-1, 0)
            delay(500)
			FR_avoid();
		case 3://FL+FR
            robot_move(-1, 0)
            delay(500)
			FL_FR_avoid();
		case 4://BL
            robot_move(1, 0)//move forward
            delay(500)
			BL_avoid();
        case 5://FL+BL
            FL_BL_avoid();
    
        case 8://BR
            BR_avoid();
        case 10://FR+BR
            FR_BR_avoid();
        case 12://BL+BR
            BL_BR_avoid();
}