#pragma config(Sensor, in1,    long_distance_R_pin, sensorAnalog)
#pragma config(Sensor, in2,    long_distance_M_pin, sensorAnalog)
#pragma config(Sensor, in3,    long_distance_L_pin, sensorAnalog)
#pragma config(Sensor, in4,    short_distance_T_pin, sensorAnalog)
#pragma config(Sensor, in5,    line_BR_pin,        sensorAnalog)
#pragma config(Sensor, in6,    line_FR_pin,        sensorAnalog)
#pragma config(Sensor, in7,    line_FL_pin,        sensorAnalog)
#pragma config(Sensor, in8,    line_BL_pin,        sensorAnalog)
#pragma config(Sensor, dgtl1,  wheel_L_encoderA_pin, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  wheel_R_encoderA_pin, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  limit_switch_A_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl6,  limit_switch_B_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl7,  limit_switch_C_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl8,  limit_switch_D_pin,      sensorDigitalIn)
#pragma config(Sensor, dgtl9,  magneto_north_pin,  sensorDigitalIn)
#pragma config(Sensor, dgtl10, magneto_south_pin,  sensorDigitalIn)
#pragma config(Sensor, dgtl11, magneto_east_pin,   sensorDigitalIn)
#pragma config(Sensor, dgtl12, magneto_west_pin,   sensorDigitalIn)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           motor_R,       tmotorVex393_MC29, PIDControl, encoderPort, dgtl3)
#pragma config(Motor,  port7,           motor_L,       tmotorVex393_MC29, PIDControl, reversed, encoderPort, dgtl1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "localisation_config.h"
#include "support.c"
#include "odometry.c"

/* _____________________________________________________________________________________________________________________

GLOBAL VARIABLES
_____________________________________________________________________________________________________________________ */

// Robot State
static float robot_x;
static float robot_y;
static float robot_yaw;
static float robot_linX;
static float robot_angZ;

static float robot_arm_position;

// robot twist
static float robot_cmd_rpmR;
static float robot_cmd_rpmL;
static float robot_cmd_linX;
static float robot_cmd_angZ;

static float robot_cmd_arm;

// robot encoders
static float robot_en_rpmR;
static float robot_en_rpmL;
static float robot_en_linX;
static float robot_en_angZ;

// magnetometer
static float magnetometer_yaw;

// robot line sensors
static int robot_line_FL;
static int robot_line_BL;
static int robot_line_BR;
static int robot_line_FR;

// robot distance sensors
static float distance_sensor_left;
static float distance_sensor_right;
static float distance_sensor_top;
static float distance_sensor_mid;

// TEST CODE BEGIN
float calc_linear_x(float rpmL, float rpmR){
	float linX = (rpmR + rpmL) / RADIAN_T0_RPM * WHEEL_DIAMETER /4;
	return linX;
}

float calc_angular_z(float rpmL, float rpmR){
	float angZ = (rpmR - rpmL) * WHEEL_DIAMETER/ROBOT_TRACK / RADIAN_T0_RPM / DEGREE_TO_RADIAN;
	return angZ;
}
// TEST CODE END

/* _____________________________________________________________________________________________________________________

SENSORS
_____________________________________________________________________________________________________________________ */
void read_sensors(){
    magnetometer_yaw = wrap_angle(read_compass(SensorValue[magneto_north], SensorValue[magneto_south], SensorValue[magneto_east], SensorValue[magneto_west]) - MAGNETOMETER_OFFSET);

    limit_switch_A = SensorValue[limit_switch_A_pin];
    limit_switch_B = SensorValue[limit_switch_B_pin];
    limit_switch_C = SensorValue[limit_switch_C_pin];
    limit_switch_D = SensorValue[limit_switch_D_pin];

	line_FL_val = filter_line_FL(SensorValue[line_FL_pin]);
	line_BL_val = filter_line_BL(SensorValue[line_BL_pin]);
	line_BR_val = filter_line_BR(SensorValue[line_BR_pin]);
	line_FR_val = filter_line_FR(SensorValue[line_FR_pin]);

	distance_sensor_mid = calculate_long_distance(filter_distance_mid(SensorValue[long_distance_M_pin])) - MID_SENSOR_OFFSET;
	distance_sensor_top = calculate_short_distance(filter_distance_top(SensorValue[short_distance_T_pin])) - TOP_SENSOR_OFFSET;
	distance_sensor_left = calculate_long_distance(filter_distance_L(SensorValue[long_distance_L_pin])) - LEFT_SENSOR_OFFSET;
	distance_sensor_right = calculate_long_distance(filter_distance_R(SensorValue[long_distance_R_pin])) - RIGHT_SENSOR_OFFSET;

    robot_en_rpmL = getMotorEncoder(motor_L) * 60/DT /ENCODER_RESOLUTION;
	robot_en_rpmR = getMotorEncoder(motor_R) * 60/DT /ENCODER_RESOLUTION;
    // TEST CODE BEGIN
    robot_en_linX = calc_linear_x(robot_en_rpmL, robot_en_rpmR);
    robot_en_angZ = calc_angular_z(robot_en_rpmL, robot_en_rpmR);
    // TEST CODE END
	resetMotorEncoder(motor_R);
	resetMotorEncoder(motor_L);
}

void update_robot_odom(){
    update_odometry(robot_x, robot_y, robot_yaw, robot_linX, robot_angZ, robot_cmd_linX, robot_cmd_angZ, robot_en_rpmL, robot_en_rpmR, magnetometer_yaw);
    robot_x = get_robot_x();
    robot_y = get_robot_y();
    robot_yaw = get_robot_yaw();
    robot_linX = get_robot_linX();
    robot_angZ = get_robot_angZ();
    return;
}

void robot_execute(){
	robot_base_move(robot_cmd_linX, robot_cmd_angZ);
	robot_cmd_linX = get_cmd_linX();
	robot_cmd_angZ = get_cmd_angZ();
	robot_cmd_rpmL = get_cmd_rpmL();
	robot_cmd_rpmR = get_cmd_rpmR();

	robot_arm_move(robot_cmd_arm);
}

/* _____________________________________________________________________________________________________________________

TASKS
_____________________________________________________________________________________________________________________ */

/**
 * @brief Initialises the robot
*/
void init(){
	int ready = 0;
	while (ready != 1){
		read_sensors();

		// Init arm
		if (robot_arm_position < 180.0){
			robot_arm_move(180.0);
		}
		else{
			robot_arm_move(0.0);
		}

		// Reset encoders
		resetMotorEncoder(motor_L);
		resetMotorEncoder(motor_R);

        // Reset odom
        robot_x = 0.0;
        robot_y = 0.0;
        robot_yaw = 0.0;
        robot_linX = 0.0;
        robot_angZ = 0.0;

		// Ready criteria
		if (robot_arm_position < ARM_TOLERANCE){
			ready = 1;
			break;
		}
	}
}

// TEST CODE BEGIN
// moves robot forward by a distance in [metre]
float move_distance(float distance_forward){
    if (robot_x < distance_forward){
        return 0.2;
    }
    else {
        return 0.0;
    }
}

// TEST CODE END

task main()
{
	init_robot();
	while(1){
		clearTimer(T1);
        read_sensors();
        update_robot_odom();
        robot_execute();
		// main Loop

        robot_cmd_linX = move_distance(1.0);
		
        // end of main loop
		while (time1[T1] < DT * 1000){}
	}
}