#include "edge_detection.h"

//Line_Sensor define in sensor.h
//  line_sensor_FL = HIGH/LOW
//  line_sensor_BL = HIGH/LOW
//  line_sensor_BR = HIGH/LOW
//  line_sensor_FR = HIGH/LOW

void edge_detected(){
//Check FL sensor detect state
    if (line_sensor_FL == HIGH) {
        FL_value = 1;
    } else {
        FL_value = 0;}
//Check FR sensor detect state
    if (line_sensor_FL == HIGH) {
        FR_value = 1;
    } else {
        FR_value = 0;}
//Check BL sensor detect state
    if (line_sensor_FL == HIGH) {
        BL_value = 1;
    } else {
        BL_value = 0;}
//Check BR sensor detect state
    if (line_sensor_FL == HIGH) {
        BR_value = 1;
    } else {
        BR_value = 0;}

Edge_detected_value =  FL_value * 1 + FR_value * 2 + BL_value * 4 + BL_value * 8;
//The value of Edge_detected_value can be 0-16, Corresponding to the 16 possible detect results of 4 IR sensors
}

void avoid_edge(){
//Run after detecting the edge. 
//Control the robot to perform different motions based on the different detect results.



}