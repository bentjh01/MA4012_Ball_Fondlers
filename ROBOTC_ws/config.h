#ifndef CONFIG_H
#define CONFIG_H

// #include <cmath.h>
// Global Variables
extern unsigned int touch_status;
extern unsigned int counter;

// TUNABLE PARAMETERS
#define LINE_SENSOR_THRESHOLD 512 // may need to tune for every sensor

// DELIVER TASK
// constexpr float delivery_pid_kp = 1.0;
// constexpr float delivery_pid_ki = 0.0;
// constexpr float delivery_pid_kd = 0.0;

#define DELIVERY_AREA_BEARING 50 // [degrees]

// GLOBAL VARIABLES
extern int task_state;
extern int dt;

// CONSTANTS
#define PERIOD = 1000;
// constexpr float max_wheel_rpm = 100; // rpm
// constexpr float wheel_diameter = 0.069; //m
// constexpr float robot_track = 0.213; //m

// #define MAX_SPEED wheel_diameter * max_wheel_rpm/ (4 * M_PI * 60)
// #define MAX_ANGULAR_SPEED (2 * MAX_SPEED) / robot_track
// #define ALLOWABLE_SPEED (angular_speed) (MAX_SPEED - angular_speed*robot_track/2)
#define MAX_RPM 100 // [rpm]

#endif // CONFIG_H