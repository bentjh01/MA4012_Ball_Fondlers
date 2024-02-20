#include "blink_led.h"

void blink_led(int duration){
	digitalWrite(led_pin, HIGH);
	delay(duration);
	digitalWrite(led_pin, LOW);
	delay(duration);
}

