#include "blink_led.h"

void init_led(void){
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

void increment_counter(dummy counter){
	counter.count++;
	Serial.println(counter.count);
}

void increment_counter(dummy* counter){
	counter->count++;
	Serial.println(counter->count);
}