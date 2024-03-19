#include "touch_sensor.h"

int init_touch_sensor(void){
	#pragma config(Sensor, TOUCH_PIN, TOUCH, sensorDigitalIn)
	return 1;
}

int read_touch_sensor(void){
	touch_status = SensorValue[TOUCH_PIN];
	return touch_status;
}

unsigned int increment_counter(unsigned int counter){
	counter ++;
	return counter
}