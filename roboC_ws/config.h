#ifndef CONFIG_H
#define CONFIG_H

#include "components/motor_control.c"

#define LINE_FL_THRESHOLD 106.0
#define LINE_BL_THRESHOLD 344.0
#define LINE_BR_THRESHOLD 173.0
#define LINE_FR_THRESHOLD 138.0

#define DT 0.05

// DELIVER TASK
#define DELIVERY_YAW_TOLERANCE 5 // [degrees] Tolerance for the yaw angle to be considered as 0 for robot to move linearly
#define DELIVER_KP 1.0
#define DELIVER_KI 0.0
#define DELIVER_KD 0.0

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

// TASK PARAMETERS
#define DT                  0.05

// ROBOT PARAMETERS
#define WHEEL_DIAMETER      0.069 //m
#define ROBOT_TRACK         0.213 //m
#define ENCODER_RESOLUTION  360.0 // [ticks/revolution]
#define MAX_WHEEL_RPM       100.0 // [rpm]
#define MAX_SPEED           0.5 // [m/s] Maximum linear speed
#define MAX_TURN            0.5 // [rad/s] Maximum angular speed

// PINOUT
#define wheel_L_encoderA    dgtl2
#define wheel_R_encoderA    dgtl4
#define servo               port2
#define motor_R             port6
#define motor_L             port7

#endif //CONFIG_#define LINE_FL_THRESHOLD 106
