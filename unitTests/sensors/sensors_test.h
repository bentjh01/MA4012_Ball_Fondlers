#ifndef SENSORS_CONFIG_H
#define SENSORS_CONFIG_H

/*______________________________________________________________________________________________________________________

SENSORS
______________________________________________________________________________________________________________________*/

// SHARP DISTANCE SENSOR
#define MID_SENSOR_OFFSET 0.0
#define TOP_SENSOR_OFFSET 0.0
#define LEFT_SENSOR_OFFSET 0.0
#define RIGHT_SENSOR_OFFSET 0.0

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
#define FILTER_GAIN_LINE_FL 	1.0 //TODO
#define FILTER_GAIN_LINE_BL 	1.0 //TODO
#define FILTER_GAIN_LINE_BR 	1.0 //TODO
#define FILTER_GAIN_LINE_FR 	1.0 //TODO
#define FILTER_GAIN_LONG_L 	    1.0 //TODO
#define FILTER_GAIN_LONG_R 	    1.0 //TODO
#define FILTER_GAIN_LONG_MID 	1.0 //TODO
#define FILTER_GAIN_SHORT_TOP 	1.0 //TODO

// MAGNETOMETER PARAMETERS
#define MAGNETOMETER_OFFSET -180.0 // compass reading when robot is facing forward i.e. the bearing of a real compass

/*______________________________________________________________________________________________________________________

FIXED PARAMETERS
______________________________________________________________________________________________________________________*/

// TASK PARAMETERS
#define DT                  0.05
#define INVALID             9999

// ROBOT PARAMETERS
#define WHEEL_DIAMETER      0.069 //m TODO
#define ROBOT_TRACK         0.213 //m TODO
#define ENCODER_RESOLUTION  360.0 // [ticks/revolution]
#define MAX_WHEEL_RPM       100.0 // [rpm]

// BEARING DEFINITION
#define NORTH           0.0
#define NORTH_WEST      45.0
#define WEST            90.0
#define SOUTH_WEST      135.0
#define NORTH_EAST      -45.0
#define EAST            -90.0
#define SOUTH_EAST      -135.0
#define SOUTH           -180.0

// MATH CONSTANTS AND CONVERSIONS
#define M_PI                3.14159265358979323846
#define DEGREE_TO_RADIAN    M_PI/180.0
#define RADIAN_T0_RPM       30.0/M_PI
#define mVOLT_TO_VOLT       0.001

#endif // SENSORS_CONFIG_H