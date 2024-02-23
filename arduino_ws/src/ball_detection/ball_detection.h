#ifndef BALL_DETECTION_H // prevents duplicate definition of the same library
#define BALL_DETECTION_H

#include <Arduino.h>
#include <math.h> //will be used later to convert analogRead() to distance in cm

extern float search_timer;
extern int l_long_pin;
extern int r_long_pin;
extern int c_long_pin;
extern int c_short_pin;

float sense_long_distance(int pin_num);
float sense_short_distance(int pin_num);
int read_long_status(int pin_num);
int read_short_status(int pin_num);

void change_search_position();
int detect_ball(bool startup_phase);
int go_to_detection(int status, bool startup_phase);

#endif // BALL_DETECTION_H
