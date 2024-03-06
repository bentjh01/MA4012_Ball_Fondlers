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
#define NORTH_EAST -45
#define EAST -90
#define SOUTH_EAST -135
#define SOUTH 180
#define SOUTH_WEST 135
#define WEST 90
#define NORTH_WEST 45
#define INVALID 360

extern int compass_bearing;

void read_sensors();

#endif // SENSORS_H