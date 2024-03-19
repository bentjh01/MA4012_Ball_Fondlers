#include "blink_led.h"

void init_blinky(void){
	#pragma config(Sensor, LED_PIN, LED, sensorDigitalOut)
}

void blinky(void){
	static unsigned int status;
	if (status == 0){
		status = 1;
	}
	else{
		status =1;
	}
	SensorValue[LED_PIN] = status;
}
