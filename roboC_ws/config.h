#ifndef CONFIG_H
#define CONFIG_H
/*______________________________________________________________________________________________________________________

TUNING SENSOR PARAMETERS
______________________________________________________________________________________________________________________*/
// SHARP DISTANCE SENSOR (measured on 6 April 2024)
#define MID_SENSOR_OFFSET 15.23
#define TOP_SENSOR_OFFSET -10.0
#define LEFT_SENSOR_OFFSET 1.5
#define RIGHT_SENSOR_OFFSET 1.9

#define FILTER_GAIN_LONG_L 	    0.5 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LONG_R 	    0.50 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LONG_MID 	0.5 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_SHORT_TOP 	1.0 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define BALL_IN_CHAMBER_DISTANCE 0.8 // [cm]
#define BALL_THRESHOLD_LNR          	35.0 //cm wrt to edge of ramp
#define BALL_THRESHOLD_MID          	35.0 //cm wrt to edge of ramp
#define OPP_CLOSENESS_THRESHOLD     	35.0 //cm wrt to edge of ramp
#define OPP_DIFFERENTIATION_THRESHOLD	8.0 //cm
#define READY_TO_COLLECT_THRESHOLD  	4.0 //cm wrt to edge of ramp

#define BALL_THRESHOLD_CHANGE 20.0 // cm
#define LIMIT_DISTANCE_READINGS 40.0 //
#define OPP_DETECT_THRESHOLD 15.0 // cm
#define FLAT_SURFACE_THRESHOLD 10.0 // cm

// LINE SENSOR
#define LINE_FL_THRESHOLD       1252.0 // Midpoint of black point and yellow point
#define LINE_BL_THRESHOLD       1147.0 // Midpoint of black point and yellow point
#define LINE_BR_THRESHOLD       1114.75 // Midpoint of black point and yellow point
#define LINE_FR_THRESHOLD       1320.0// Midpoint of black point and yellow point

#define FILTER_GAIN_LINE_FL 	0.60 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LINE_BL 	0.60 // (output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LINE_BR 	0.60 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)
#define FILTER_GAIN_LINE_FR 	0.60 //(output = prev_input) 0 < FILTER_GAIN < 1 (output = new_input)

// MAGNETOMETER PARAMETERS
#define MAGNETOMETER_OFFSET 180.0 // [deg]
// #define MAGNETOMETER_OFFSET 45.0 // [deg]

/*______________________________________________________________________________________________________________________

TUNING MOTOR PARAMETERS
______________________________________________________________________________________________________________________*/

// ENCODERS
#define FILTER_ENCODER 0.5

// DRIVE
#define MOTOR_L_KP 0.9
#define MOTOR_L_KI 0.005
#define MOTOR_L_KD 0.00
#define MOTOR_L_INTEGRAL_MAX 127

#define MOTOR_R_KP 0.9
#define MOTOR_R_KI 0.005
#define MOTOR_R_KD 0.00
#define MOTOR_R_INTEGRAL_MAX 127

// SERVO
#define SERVO_TOLERANCE 7.0 // [deg] TODO
#define SERVO_POSITION_GAIN 7.50 // [deg] TODO
#define SERVO_KP 0.8
#define SWITCH_A_POSITION 0.0 //[deg] TODO
#define SWITCH_B_POSITION 90.0 //[deg] TODO
#define SWITCH_C_POSITION 180.0 //[deg] TODO

/*______________________________________________________________________________________________________________________

TUNING ODOMETRY PARAMETERS
______________________________________________________________________________________________________________________*/

// ROBOT POSE
#define ENCODER_FILTER 0.5  // TODO [0,1] takes a value between 0 and 1, the closer to 1 the more filtering
#define MAGNETO_FILTER 1.0 // TODO [0,1] takes a value between 0 and 1, the closer to 1 the more filtering

#define LINEAR_TOLERANCE 0.05 //TODO
#define YAW_TOLERANCE 22.50 // [deg] TODO

#define MOTOR_ACCL_LIM 100.0 // [rpm]

/*______________________________________________________________________________________________________________________

TUNABLE TASK PARAMETERS
______________________________________________________________________________________________________________________*/

// EDGE TASK
#define EDGE_REVERSE_DISTANCE_SMALL 0.05 // [m] TODO
#define EDGE_REVERSE_DISTANCE_BIG 0.15
#define EDGE_YAW_KP 0.6

// HOME TASK
#define HOME_AWAY_DISTANCE (ARENA_X * 1.0 / 2.0)

// SEARCH TASK
#define SEARCH_COUNT_THRESHOLD      75
#define CHANGE_POSITION_DISTANCE    0.3
//#define DISTANCE_CHANGE_THRESHOLD		10.0

// GOTO TAS4
#define GOTO_SWEEP_TIME         3.0
#define GOTO_ALIGN_BALL_GAIN    0.833
#define GOTO_CURVE_LIN_SPEED    0.2
#define GOTO_CURVE_ANG_SPEED    30.0
#define BACK_TO_SEARCH_COUNT		30

// COLLECT TASK
#define SERVO_COLLECT_POSITION 90.0

// DELIVERY TASK
#define DELIVER_YAW_KP 0.6
#define SERVO_DELIVER_POSITION 180.0 //TODO
#define DELIVERY_SERVO_COUNTER   20 //TODO

/*______________________________________________________________________________________________________________________

FIXED PARAMETERS
______________________________________________________________________________________________________________________*/

// MATH CONSTANTS AND CONVERTIONS
#define M_PI                3.141593
#define E                   2.718282
#define DEGREE_TO_RADIAN    0.017453
#define RADIAN_T0_RPM       9.549297
#define mVOLT_TO_VOLT       0.001

// ROBOTC CONSTANTS
#define TRIGGERED           0       // VEX Cortex is all pull-up
#define NOT_TRIGGERED       1
#define MAX_POWER           127
#define SUCCESS             1
#define FAIL                0
#define INVALID             9999

// TASK PARAMETERS
#define DT_MAIN                  0.05
#define DT_READ                  0.05
#define EDGE                1
#define HOME                2
#define SEARCH              3
#define GOTO                4
#define COLLECT             5
#define DELIVER             6

// ROBOT PARAMETERS
#define ROBOT_WIDTH         0.3//m
#define WHEEL_DIAMETER      0.06926 //m
#define ROBOT_TRACK         0.213 //m
#define ENCODER_RESOLUTION  360.0 // [ticks/revolution]
#define MAX_WHEEL_RPM       100.0// [rpm]
#define MAX_SPEED           MAX_WHEEL_RPM/RADIAN_T0_RPM*WHEEL_DIAMETER/2 // [m/s]
#define MAX_TURN            MAX_WHEEL_RPM/RADIAN_T0_RPM*WHEEL_DIAMETER/ROBOT_TRACK/DEGREE_TO_RADIAN // [deg/s]

// ARENA PARAMETERS
#define ARENA_X        2.4 // [m] Length
#define ARENA_Y        1.2 // [m] Width
#define ARENA_BEARING    0.0 // [degrees] North
#define FRONT_WALL  12
#define BACK_WALL   6
#define LEFT_WALL   9
#define RIGHT_WALL  3

// BEARING DEFINITION
#define NORTH           0.0
#define NORTH_WEST      45.0
#define WEST            90.0
#define SOUTH_WEST      135.0
#define NORTH_EAST      -45.0
#define EAST            -90.00
#define SOUTH_EAST      -135.0
#define SOUTH           -180.0

//Chen test
#define SCALE_RPM 0.98

#endif // CONFIG_H