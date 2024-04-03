#ifndef SENSOR_TEST_H
#define SENSOR_TEST_H
/*______________________________________________________________________________________________________________________

TUNING SENSOR PARAMETERS
______________________________________________________________________________________________________________________*/
// SHARP DISTANCE SENSOR
#define MID_SENSOR_OFFSET -13.27
#define TOP_SENSOR_OFFSET 21.5 //TODO
#define LEFT_SENSOR_OFFSET 1.5
#define RIGHT_SENSOR_OFFSET 2.9

#define FILTER_GAIN_LONG_L 	    1.0 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LONG_R 	    1.0 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LONG_MID 	1.0 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_SHORT_TOP 	1.0 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define BALL_IN_CHAMBER_DISTANCE 0.0 // [cm] TODO

// LINE SENSOR
// BENS ROOM
#define LINE_FL_THRESHOLD       348.0 // Midpoint of black point and yellow point
#define LINE_BL_THRESHOLD       188.0 // Midpoint of black point and yellow point
#define LINE_BR_THRESHOLD       307.0 // Midpoint of black point and yellow point
#define LINE_FR_THRESHOLD       187.0 // Midpoint of black point and yellow point
// ARENA
// #define LINE_FL_THRESHOLD       106.0 // Midpoint of black point and yellow point
// #define LINE_BL_THRESHOLD       344.0 // Midpoint of black point and yellow point
// #define LINE_BR_THRESHOLD       173.0 // Midpoint of black point and yellow point
// #define LINE_FR_THRESHOLD       1385.0 // Midpoint of black point and yellow point

#define FILTER_GAIN_LINE_FL 	1.0 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LINE_BL 	1.0 // (output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LINE_BR 	1.0 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LINE_FR 	1.0 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)

// MAGNETOMETER PARAMETERS
#define MAGNETOMETER_OFFSET 180.0 // [deg] 

/*______________________________________________________________________________________________________________________

FIXED PARAMETERS
______________________________________________________________________________________________________________________*/

// MATH CONSTANTS AND CONVERTIONS
#define M_PI                3.141593
#define E                   2.718282
#define DEGREE_TO_RADIAN    M_PI/180
#define RADIAN_T0_RPM       30/M_PI
#define mVOLT_TO_VOLT       0.001

// GPIO CONSTANTS
#define TRIGGERED           0
#define NOT_TRIGGERED           0
#define MAX_POWER           127.0
#define SUCCESS             1
#define FAIL             0
#define INVALID             9999

// TASK
#define DT                  0.05

// BEARING DEFINITION
#define NORTH           0.0
#define NORTH_WEST      45.0
#define WEST            90.0
#define SOUTH_WEST      135.0
#define NORTH_EAST      -45.0
#define EAST            -90.0
#define SOUTH_EAST      -135.0
#define SOUTH           -180.0

#endif