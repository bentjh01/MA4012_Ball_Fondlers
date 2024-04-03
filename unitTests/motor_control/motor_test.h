#ifndef MOTOR_CONTROL_CONFIG_H
#define MOTOR_CONTROL_CONFIG_H

/*______________________________________________________________________________________________________________________

TUNING MOTOR PARAMETERS
______________________________________________________________________________________________________________________*/

// DRIVE
#define EXPONENT_GAIN 0.0215
#define RPM_GAIN 11.627

#define MOTOR_L_KP 0.5 //TODO
#define MOTOR_L_KI 1.2 //TODO
#define MOTOR_L_KD 0.001 //TODO

#define MOTOR_R_KP 0.5 //TODO
#define MOTOR_R_KI 1.2 //TODO
#define MOTOR_R_KD 0.001 //TODO

// SERVO
#define ARM_TOLERANCE 5.0 // [deg] TODO
#define SERVO_POSITION_GAIN 1.0 // [deg] TODO
#define SWITCH_A_POSITION 0.0 //[deg] TODO
#define SWITCH_B_POSITION 0.0 //[deg] TODO
#define SWITCH_C_POSITION 0.0 //[deg] TODO

/*______________________________________________________________________________________________________________________

FIXED PARAMETERS
______________________________________________________________________________________________________________________*/

// MATH CONSTANTS AND CONVERTIONS
#define M_PI                3.141593
#define E                   2.718282
#define DEGREE_TO_RADIAN    M_PI/180
#define RADIAN_T0_RPM       30/M_PI
#define mVOLT_TO_VOLT       0.001

// ROBOTC CONSTANTS
#define TRIGGERED           0
#define MAX_POWER 127.0

// TASK PARAMETERS
#define DT                  0.05

// ROBOT PARAMETERS
#define WHEEL_DIAMETER      0.06926 //m
#define ROBOT_TRACK         0.213 //m
#define ENCODER_RESOLUTION  360.0 // [ticks/revolution]
#define MAX_WHEEL_RPM       100.0 // [rpm]

#endif // MOTOR_CONTROL_CONFIG_H