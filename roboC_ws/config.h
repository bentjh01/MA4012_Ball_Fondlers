#ifndef CONFIG_H
#define CONFIG_H
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
#define MAGNETOMETER_OFFSET 45.0 // [deg] TODO BEARING OF THE ROBOT WHEN AT START

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
#define SERVO_TOLERANCE 5.0 // [deg] TODO
#define SERVO_POSITION_GAIN 1.0 // [deg] TODO
#define SWITCH_A_POSITION 0.0 //[deg] TODO
#define SWITCH_B_POSITION 0.0 //[deg] TODO
#define SWITCH_C_POSITION 0.0 //[deg] TODO

/*______________________________________________________________________________________________________________________

TUNING ODOMETRY PARAMETERS
______________________________________________________________________________________________________________________*/

// ROBOT POSE
#define ENCODER_FILTER_GAIN 0.25 // TODO [0,1] takes a value between 0 and 1, the closer to 1 the more filtering
#define MAGNETO_FILTER_GAIN 0.25 // TODO [0,1] takes a value between 0 and 1, the closer to 1 the more filtering

#define LINEAR_TOLERANCE 0.1 //TODO 
#define YAW_TOLERANCE 5.0 // [deg] TODO 

/*______________________________________________________________________________________________________________________

TUNABLE TASK PARAMETERS
______________________________________________________________________________________________________________________*/

// EDGE TASK
#define EDGE_REVERSE_DISTANCE 0.05 // [m] TODO

// DELIVERY TASK
#define SERVO_DELIVER_POSITION 180.0 //TODO

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
#define NOT_TRIGGERED           0
#define MAX_POWER           127.0
#define SUCCESS             1
#define FAIL             0
#define INVALID             9999

// TASK PARAMETERS
#define DT                  0.05
#define EDGE                1   
#define HOME                2
#define SEARCH              3
#define COLLECT             4
#define DELIVER             5

// ROBOT PARAMETERS
#define WHEEL_DIAMETER      0.06926 //m
#define ROBOT_TRACK         0.213 //m
#define ENCODER_RESOLUTION  360.0 // [ticks/revolution]
#define MAX_WHEEL_RPM       100.0 // [rpm]
#define MAX_SPEED           MAX_WHEEL_RPM/RADIAN_T0_RPM*WHEEL_DIAMETER/2 // [m/s]
#define MAX_TURN            MAX_WHEEL_RPM/RADIAN_T0_RPM*WHEEL_DIAMETER/ROBOT_TRACK/DEGREE_TO_RADIAN // [deg/s]

// ARENA PARAMETERS
#define ARENA_X        2.4 // [m] Length
#define ARENA_Y        1.2 // [m] Width
#define ARENA_BEARING    0.0 // [degrees] North

// BEARING DEFINITION
#define NORTH           0.0
#define NORTH_WEST      45.0
#define WEST            90.0
#define SOUTH_WEST      135.0
#define NORTH_EAST      -45.0
#define EAST            -90.0
#define SOUTH_EAST      -135.0
#define SOUTH           -180.0

#endif // CONFIG_H