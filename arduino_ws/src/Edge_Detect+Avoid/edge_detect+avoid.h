#ifndef EDGE_DETECTION_H // prevents duplicate definition of the same library
#define EDGE_DETECTION_H

// <> means it's a global library i.e. built-in libraries such as Wire.h, SPI.h, etc.
#include <Arduino.h> 
// "" means it's a local library i.e. libraries that we created. local libraries are relative.
// .. means go up one directory.
#include "arduino_ws/src/config.h"
#include "arduino_ws/src/sensors/sensors.h" 
#include "arduino_ws/src/hardware/hardware.h"


extern int Edge_detected_value

void edge_detected();
void avoid_edge();

//void Turn_Right();
//void Turn_Left();
//void Move_Forward();
//void Move_Backward();
//void Stop();


#endif
