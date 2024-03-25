#ifndef SENSORS_CONFIG_H
#define SENSORS_CONFIG_H

// SENSOR PARAMETERS
//TODO-ARENA
// #define LINE_FL 106
// #define LINE_BL 344
// #define LINE_BR 173
// #define LINE_FR 1385

// BENS ROOM
#define LINE_FL 106
#define LINE_BL 344
#define LINE_BR 173
#define LINE_FR 1385

#define CUTOFF_LINE_FL 	1 // [Hz]
#define CUTOFF_LINE_BL 	1 // [Hz]
#define CUTOFF_LINE_BR 	1 // [Hz]
#define CUTOFF_LINE_FR 	1 // [Hz]
#define CUTOFF_LONG_L 	1 // [Hz]
#define CUTOFF_LONG_R 	1 // [Hz]
#define CUTOFF_LONG_T 	1 // [Hz]
#define CUTOFF_SHORT 	1 // [Hz]

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

#endif // SENSORS_CONFIG_H