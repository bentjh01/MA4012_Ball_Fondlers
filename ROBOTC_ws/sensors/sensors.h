#ifndef SENSORS_H
#define SENSORS_H

#include <math.h>
#include "../pinout.h"
#include "../config.h"

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

//compass definitions
#define NORTH 0
#define NORTH_EAST -45
#define EAST -90
#define SOUTH_EAST -135
#define SOUTH 180
#define SOUTH_WEST 135
#define WEST 90
#define NORTH_WEST 45

//sharp distance sensor definitions
#define LONG_DIST_LOWER_THRESHOLD_CM 25     //lower threshold of long dist sensor 25 cm
#define LONG_DIST_UPPER_THRESHOLD_CM 45     //upper threshold of long dist sensor 45 cm
#define SHORT_DIST_THRESHOLD_CM 10          //upper threshold of short dist sensor 10 cm.
#define VOLTAGE_SCALE (5.0/1023.0)

extern int compass_bearing;

void init_sensors();
void read_all_sensors();

void read_line_sensors(void);
void read_distance_sensors(void);
void read_limit_switches(void);
void read_compass(void);

float read_long_sensor_distance(int pin_num);
float read_short_sensor_distance(int pin_num);
int read_digitized_long_sensor_distance(int pin_num);
int read_digitized_short_sensor_distance(int pin_num);

#endif // SENSORS_H
