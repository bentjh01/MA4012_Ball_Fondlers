#ifndef CONFIG_H
#define CONFIG_H

#include "components/motor_control.c"

#define LINE_FL_THRESHOLD 106.0
#define LINE_BL_THRESHOLD 344.0
#define LINE_BR_THRESHOLD 173.0
#define LINE_FR_THRESHOLD 138.0

// MAIN LOOP PARAMETERS
#define DT 0.05
#define HOME                1
#define SEARCH_BALL         2
#define GOTO_BALL           3
#define COLLECT_BALL        4
#define DELIVER_BALL        5
// #define OPP_DETECTED        9

//SHARP DISTANCE SENSORS
#define BALL_THRESHOLD_LNR          45.0
#define BALL_THRESHOLD_MID          35.0
#define OPP_CLOSENESS_THRESHOLD     15.0
#define READY_TO_COLLECT_THRESHOLD  4.0

//SEARCH TASK
#define SEARCH_YAW_TOLERANCE        2.0
#define SEARCH_COUNT_THRESHOLD      25
#define CHANGE_POSITION_DISTANCE    80.0

//GOTO TASK
#define GOTO_YAW_TOLERANCE  5.0

// DELIVER TASK
#define DELIVERY_YAW_TOLERANCE 5.0 // [degrees] Tolerance for the yaw angle to be considered as 0 for robot to move linearly

// MOTORS
#define MOTOR_L_KP 0.0
#define MOTOR_L_KI 0.0
#define MOTOR_L_KD 0.0

#define MOTOR_R_KP 0.588671875
#define MOTOR_R_KI 0.0
#define MOTOR_R_KD 0.0

// SERVO
#define SERVO_DISPLACEMNT_FACTOR 1.0 // TODO
#define SERVO_POWER_FACTOR 1.0 // TODO

// CONSTANTS
#define M_PI                3.14159265358979323846
#define DEGREE_TO_RADIAN    M_PI/180
#define RADIAN_T0_RPM       30/M_PI
#define NULL                999

// TASK PARAMETERS
#define DT                  0.05

// ROBOT PARAMETERS
#define WHEEL_DIAMETER      0.069 //m
#define ROBOT_TRACK         0.213 //m
#define ENCODER_RESOLUTION  360.0 // [ticks/revolution]
#define MAX_WHEEL_RPM       100.0 // [rpm]
#define MAX_SPEED           0.5 // [m/s] Maximum linear speed
#define MAX_TURN            0.5 // [rad/s] Maximum angular speed

// MAGNETOMETER PARAMETERS
#define NORTH           0
#define NORTH_WEST      45
#define WEST            90
#define SOUTH_WEST      135
#define SOUTH           180
#define NORTH_EAST      -45
#define EAST            -90
#define SOUTH_EAST      -135
#define SOUTH           180

// PINOUT
#define wheel_L_encoderA    dgtl1
#define wheel_R_encoderA    dgtl3
#define limit_switch        dgtl5
#define limit_switch        dgtl6
#define limit_switch        dgtl7
#define limit_switch        dgtl8
#define compass_north       dgtl9
#define compass_south       dgtl10
#define compass_east        dgtl11
#define compass_west        dgtl12
#define long_distance_R     in1
#define long_distance_L     in2
#define long_distance_M     in3
#define short_distance_T    in4
#define line_BR             in5
#define line_FR             in6
#define line_FL             in7
#define line_BL             in8
#define servo               port2
#define motor_R             port6
#define motor_L             port7

#endif //CONFIG_#define LINE_FL_THRESHOLD 106
