#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <math.h>
#include "../config.h"
#include "../hardware/hardware.h"

extern int line_sensor_FL;
extern int line_sensor_BL;
extern int line_sensor_BR;
extern int line_sensor_FR;

extern float long_distance_sensor_FL;
extern float long_distance_sensor_FR;
extern float long_distance_sensor_TP;
extern float short_distance_sensor;

extern int limit_switch_chamber;
extern int limit_switch_BL;
extern int limit_switch_BR;

#define NORTH 0
#define NORTH_EAST 1
#define EAST 2
#define SOUTH_EAST 3
#define SOUTH 4
#define SOUTH_WEST 5
#define WEST 6
#define NORTH_WEST 7
#define INVALID -1
extern int compass_bearing;

void read_sensors();

#endif // SENSORS_H