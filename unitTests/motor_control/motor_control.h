#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

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
#define ENCODER_RESOLUTION  360 // [ticks/revolution]
#define MAX_WHEEL_RPM       100 // [rpm]

#endif // MOTOR_CONTROL_H