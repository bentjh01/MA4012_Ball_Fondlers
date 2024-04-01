#ifndef MOTOR_CONTROL_CONFIG_H
#define MOTOR_CONTROL_CONFIG_H

// MOTORS
#define LINEAR_SPEED_FACTOR 0.1511 // TODO
#define LINEAR_SPEED_OFFSET -0.3419 // TODO

#define MOTOR_L_KP 0.588671875*1.60
#define MOTOR_L_KI 0.0
#define MOTOR_L_KD 0.0

// #define MOTOR_R_KP 0.588671875*2.00
#define MOTOR_R_KP 0.0
#define MOTOR_R_KI 0.0
#define MOTOR_R_KD 0.0

// SERVO
#define SERVO_DISPLACEMNT_FACTOR 1.0 // TODO
#define SERVO_POWER_FACTOR 1.0 // TODO

// CONSTANTS
#define M_PI                3.141593
#define E                   2.718282
#define DEGREE_TO_RADIAN    M_PI/180
#define RADIAN_T0_RPM       30/M_PI

// TASK PARAMETERS
#define DT                  0.05

// ROBOT PARAMETERS
#define WHEEL_DIAMETER      0.06926 //m
#define ROBOT_TRACK         0.213 //m
#define ENCODER_RESOLUTION  360.0 // [ticks/revolution]
#define MAX_WHEEL_RPM       100.0 // [rpm]

// PINOUT
#define wheel_L_encoderA    dgtl2
#define wheel_R_encoderA    dgtl4
#define servo               port2
#define motor_R             port6
#define motor_L             port7


#endif // MOTOR_CONTROL_CONFIG_H