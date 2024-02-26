#ifndef BLINK_LED_H // prevents duplicate definition of the same library
#define BLINK_LED_H
// <> means it's a global library i.e. built-in libraries such as Wire.h, SPI.h, etc.
#include <Arduino.h> 
// "" means it's a local library i.e. libraries that we created. local libraries are relative.
// .. means go up one directory.
#include "../hardware/hardware.h" 

typedef struct LED{
  int pin;
  int blink_period;
  int last_state;
  long last_time;
} LED;

extern LED* test_led;

// function prototype
void setup_led(LED* led, int pin, int period);
void init_led(LED* led);
void blink_led(LED* led);

#endif // BLINK_LED_H
