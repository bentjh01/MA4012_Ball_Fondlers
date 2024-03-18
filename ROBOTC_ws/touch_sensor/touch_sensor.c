#include "touch_sensor.h"

unsigned int touch_status;

void init_touch_sensor(void){
	#pragma config(Sensor, TOUCH_PIN, TOUCH, sensorDigitalIn)
}

void read_touch_sensor(void){
	touch_status = SensorValue[TOUCH_PIN];
}

unsigned int counter;

void increment_counter(void){
	counter ++;
}