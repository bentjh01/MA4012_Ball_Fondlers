#include "blink_led.h"

long start_time = millis();
unsigned long time_elapsed; 
void blink_led(int duration){
	time_elapsed = millis() - start_time;
	digitalWrite(led_pin, HIGH);
	delay(duration);
	time_elapsed = millis() - start_time;
	digitalWrite(led_pin, LOW);
	delay(duration);
}

void blink_led_pointer(int* duration){
	time_elapsed = millis() - start_time;
	digitalWrite(led_pin, HIGH);
	delay(duration);
	time_elapsed = millis() - start_time;
	digitalWrite(led_pin, LOW);
	delay(duration);
}

