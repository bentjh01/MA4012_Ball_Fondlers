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


void edge_avoid(){
//Run when Edge_avoid_enabled == true.
//When detect the edge and should take actions, stop the motor first
    robot_move(0, 0);
    delay(500);
    if robot_yaw 
            
}