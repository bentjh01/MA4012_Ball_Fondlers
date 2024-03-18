#ifndef CONFIG_H
#define CONFIG_H

// SENSOR PARAMETERS
#define LINE_SENSOR_THRESHOLD 512 // may need to tune for every sensor
#define ENCODER_FILTER_GAIN 0.25 // [0,1] takes a value between 0 and 1, the closer to 1 the more filtering

// DELIVER TASK
#define delivery_pid_kp = 1.0;
#define delivery_pid_ki = 0.0;
#define delivery_pid_kd = 0.0;

#define DELIVERY_AREA_BEARING 50 // [degrees]

// GLOBAL VARIABLES

// CONSTANTS
#define M_PI 3.14159265358979323846
#define DEGREE_TO_RADIAN M M_PI/180
#define RADIAN_T0_RPM M_PI/30

// TASK PARAMETERS
#define HOME                1
#define SEARCH_BALL         2
#define GOTO_BALL           3
#define GRAB_BALL           4
#define DELIVER_BALL        5

// ROBOT PARAMETERS
#define WHEEL_DIAMETER = 0.069; //m
#define ROBOT_TRACK = 0.213; //m
#define ENCODER_RESOLUTION = 90; // [ticks/revolution]
#define MAX_WHEEL_RPM = 100; // [rpm]
#define MAX_SPEED = WHEEL_DIAMETER * MAX_WHEEL_RPM/ (4 * M_PI * 60); // [m/s]
#define MAX_ANGULAR_SPEED = (2 * MAX_SPEED) / ROBOT_TRACK; // [rad/s]

// #define MAX_SPEED wheel_diameter * max_wheel_rpm/ (4 * M_PI * 60)
// #define MAX_ANGULAR_SPEED (2 * MAX_SPEED) / robot_track
// #define ALLOWABLE_SPEED (angular_speed) (MAX_SPEED - angular_speed*robot_track/2)
// #define MAX_RPM 100 // [rpm]

#endif // CONFIG_H