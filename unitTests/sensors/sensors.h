#ifndef SENSORS_CONFIG_H
#define SENSORS_CONFIG_H


// SENSOR PARAMETERS
//sharp distance sensor definitions
#define LONG_DIST_LOWER_THRESHOLD_CM 25.0      //lower threshold of long dist sensor 25 cm
#define LONG_DIST_UPPER_THRESHOLD_CM 45.0      //upper threshold of long dist sensor 45 cm
#define SHORT_DIST_THRESHOLD_CM 20.0 //upper threshold of short dist sensor 20 cm (example only). Make this <= LOWER_THRESHOLD_CM
#define VOLTAGE_SCALE (5.0/1023.0)
//TODO-ARENA
// #define LINE_FL 106
// #define LINE_BL 344
// #define LINE_BR 173
// #define LINE_FR 1385

// BENS ROOM
#define LINE_FL 106.0
#define LINE_BL 344.0
#define LINE_BR 173.0
#define LINE_FR 1385.0

// FILTERING, (output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LINE_FL 	1.0
#define FILTER_GAIN_LINE_BL 	1.0
#define FILTER_GAIN_LINE_BR 	1.0 
#define FILTER_GAIN_LINE_FR 	1.0 
#define FILTER_GAIN_LONG_L 	    1.0 
#define FILTER_GAIN_LONG_R 	    1.0 
#define FILTER_GAIN_LONG_MID 	1.0 
#define FILTER_GAIN_SHORT_TOP 	1.0 

// CONSTANTS
#define M_PI                3.14159265358979323846
#define DEGREE_TO_RADIAN    M_PI/180.0
#define RADIAN_T0_RPM       30.0/M_PI
#define BYTE_TO_VOLT        1.0/51.0 // 

// TASK PARAMETERS
#define DT                  0.05

// ROBOT PARAMETERS
#define WHEEL_DIAMETER      0.069 //m
#define ROBOT_TRACK         0.213 //m
#define ENCODER_RESOLUTION  360.0 // [ticks/revolution]
#define MAX_WHEEL_RPM       100.0 // [rpm]



#endif // SENSORS_CONFIG_H