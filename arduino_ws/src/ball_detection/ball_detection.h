#ifndef BALL_DETECTION_H // prevents duplicate definition of the same library
#define BALL_DETECTION_H
// <> means it's a global library i.e. built-in libraries such as Wire.h, SPI.h, etc.
#include <Arduino.h> 
// "" means it's a local library i.e. libraries that we created. local libraries are relative.
// .. means go up one directory.
#include "../hardware/hardware.h" 

void change_search_position();
void detect_ball(startup_phase);
void go_to_ball();

#endif // BLINK_LED_H
