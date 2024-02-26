#ifndef BLINK_LED_H // prevents duplicate definition of the same library
#define BLINK_LED_H
// <> means it's a global library i.e. built-in libraries such as Wire.h, SPI.h, etc.
#include <Arduino.h> 
// "" means it's a local library i.e. libraries that we created. local libraries are relative.
// .. means go up one directory.
#include "../hardware/hardware.h" 

typedef struct LED{
  int t;
} LED;

extern LED* test_led;

// function prototype
void blink_led(LED* led);
void set_led(LED* led, int duration);
void incrementInteger(int* num);


#endif // BLINK_LED_H
