#ifndef BALL_DETECTION_H // prevents duplicate definition of the same library
#define BALL_DETECTION_H

#include <Arduino.h>
#include <math.h>
#include "motors.h"
#include "hardware.h"

#define LONG_DIST_LOWER_THRESHOLD_CM 25      //lower threshold of long dist sensor 25 cm
#define LONG_DIST_UPPER_THRESHOLD_CM 45      //upper threshold of long dist sensor 45 cm
#define SHORT_DIST_THRESHOLD_CM 20 //upper threshold of short dist sensor 20 cm (example only). Make this <= LOWER_THRESHOLD_CM
#define VOLTAGE_SCALE (5.0/1023.0)
#define RAD_TO_DEG (180.0 / PI)
#define BALL_TO_ROBOT_CENTER 15.0 //approx distance between the object detected by the left/right sensor wrt the center of ball collection mechanism in an axis perpendicular to robot direction. 15 cm is example only.
#define TOLERANCE_CM 5.0
#define FRACTIONAL_CLOSENESS_TO_BALL 0.80

extern float search_timer;
extern robot_moving_timeout_milisecond;

typedef struct {
	float linear_velocity;
	float angular_velocity;
  float time_setting_milisecond;
} circular_path;

float read_long_sensor_distance(int pin_num);
float read_short_sensor_distance(int pin_num);
int read_digitized_long_sensor_distance(int pin_num);
int read_digitized_short_sensor_distance(int pin_num);
int check_status_from_left_right_sensor(int long_distance_sensor_FL_status, int long_distance_sensor_FR_status);
circular_path calculate_translation_angular_speed(int pin_num, float angular_velocity_DegPerSec);
int change_search_position(bool startup_phase);
int scan(bool startup_phase);
int go_to_detection(int status, bool startup_phase);

#endif // BALL_DETECTION_H
