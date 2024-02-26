#include "blink_led.h"

LED* test_led = new LED;

void setup_led(LED* led, int pin, int period){
	led->pin = pin;
	led->blink_period = period;
}

void init_led(LED* led){
	pinMode(led->pin, OUTPUT);
}

void blink_led(LED* led){
	if (millis() - led->last_time > led->blink_period){
		led->last_time = millis();
		if (led->last_state == 0){
			led->last_state = 1;
		}
		else{
			led->last_state = 0;
		}
		digitalWrite(led->pin, led->last_state);
	}
}