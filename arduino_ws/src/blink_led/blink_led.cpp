#include "blink_led.h"

LED* test_led = new LED;

void blink_led(LED* led){
	delay(led->t);
	digitalWrite(led_pin, HIGH);
	delay(led->t);
	digitalWrite(led_pin, LOW);
}

void set_led(LED* led, int duration){
	led->t = duration;
	Serial.println(led->t);
}