
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

#include "config.h"
#include "components/components.h"
#include "robotTasks/robotTasks.h"
/* _____________________________________________________________________________________________________________________

GLOBAL VARIABLES
_____________________________________________________________________________________________________________________ */

// Robot pose
static float robot_x;
static float robot_y;
static float robot_yaw;
static float robot_linX;
static float robot_angZ;

static float robot_arm_position;
static int ball_in_chamber_status;

// robot command
static float robot_cmd_rpmR;
static float robot_cmd_rpmL;
static float robot_cmd_linX;
static float robot_cmd_angZ;

static float robot_cmd_arm;

// robot encoders
static float robot_en_rpmR;
static float robot_en_rpmL;

// robot magnetometer
static float robot_magneto_yaw;

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

// limit siwtches
static int limit_switch_A;
static int limit_switch_B;
static int limit_switch_C;
static int limit_switch_D;

// opp detection
int opp_detected;

// robot task
int task_status;
int prev_task_status;

/* _____________________________________________________________________________________________________________________

UNCONDITIONAL TASKS
_____________________________________________________________________________________________________________________ */

/// @brief Read all sensors
void read_sensors(){
    robot_magneto_yaw = read_compass(SensorValue[magneto_north_pin], SensorValue[magneto_south_pin], SensorValue[magneto_east_pin], SensorValue[magneto_west_pin]);
    robot_magneto_yaw = wrap_to_pi(robot_magneto_yaw - MAGNETOMETER_OFFSET);

    limit_switch_A = SensorValue[limit_switch_A_pin];
    limit_switch_B = SensorValue[limit_switch_B_pin];
    limit_switch_C = SensorValue[limit_switch_C_pin];
    limit_switch_D = SensorValue[limit_switch_D_pin];

	robot_line_FL = check_threshold(filter_line_FL(SensorValue[line_FL_pin]), LINE_FL_THRESHOLD);
	robot_line_BL = check_threshold(filter_line_BL(SensorValue[line_BL_pin]), LINE_BL_THRESHOLD);
	robot_line_BR = check_threshold(filter_line_BR(SensorValue[line_BR_pin]), LINE_BR_THRESHOLD);
	robot_line_FR = check_threshold(filter_line_FR(SensorValue[line_FR_pin]), LINE_FR_THRESHOLD);

	distance_sensor_mid = calculate_long_distance(filter_distance_mid(SensorValue[long_distance_M_pin])) - MID_SENSOR_OFFSET;
	distance_sensor_top = calculate_short_distance(filter_distance_top(SensorValue[short_distance_T_pin])) - TOP_SENSOR_OFFSET;
	distance_sensor_left = calculate_long_distance(filter_distance_L(SensorValue[long_distance_L_pin])) - LEFT_SENSOR_OFFSET;
	distance_sensor_right = calculate_long_distance(filter_distance_R(SensorValue[long_distance_R_pin])) - RIGHT_SENSOR_OFFSET;

	ball_in_chamber_status = check_ball_in_chamber(distance_sensor_mid);

    robot_en_rpmL = getMotorEncoder(motor_L) * 60/DT /ENCODER_RESOLUTION;
	robot_en_rpmR = getMotorEncoder(motor_R) * 60/DT /ENCODER_RESOLUTION;
    
	robot_arm_position = get_arm_position(SensorValue[limit_switch_A_pin], SensorValue[limit_switch_B_pin], SensorValue[limit_switch_C_pin]);

	resetMotorEncoder(motor_R);
	resetMotorEncoder(motor_L);
	return;
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
	set_motor_status(robot_en_rpmL, robot_en_rpmR);
	robot_base_move(robot_cmd_linX, robot_cmd_angZ);
	robot_cmd_linX = get_cmd_linX();
	robot_cmd_angZ = get_cmd_angZ();
	robot_cmd_rpmL = get_cmd_rpmL();
	robot_cmd_rpmR = get_cmd_rpmR();

	robot_arm_move(robot_cmd_arm);
	return;
}

/* _____________________________________________________________________________________________________________________

TASKS
_____________________________________________________________________________________________________________________ */

/**
 * @brief Initialises the robot
*/
void init_robot(){
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
		if (robot_arm_position < SERVO_TOLERANCE){
			ready = 1;
			break;
		}
	}
	return;
}

/* @Unizz20
void wait_for_start(start_button){
	if (start_button == pressed){
		init_robot();
		while(start_button == pressed){
			// wait for button to be released
			task_status = HOME;
		}
}
*/

task main()
{
	init_robot();
	while(1){
		clearTimer(T1);
        read_sensors();
        update_robot_odom();
        robot_execute();
		// main Loop
		if (edge_detected(robot_line_FL, robot_line_BL, robot_line_BR, robot_line_FR) == TRIGGERED){
			if (task_status != EDGE){
				prev_task_status = task_status;
			}
			task_status = EDGE;
			avoid_case_check(robot_x, robot_y, robot_yaw, robot_line_FL, robot_line_FR, robot_line_BL, robot_line_BR);
			// wall_case_check(robot_yaw, robot_line_FL, robot_line_FR, robot_line_BL, robot_line_BR); @Unizz20
		}
		else {// when avoid status == 0 
			switch (task_status){
				case EDGE:
					task_status = edge_avoid_task(robot_x, robot_y, robot_yaw, prev_task_status);
					robot_cmd_linX = get_edge_avoid_linX();
					robot_cmd_angZ = get_edge_avoid_angZ();
					break;
				case HOME:
					task_status = SEARCH;
					// task_status = home_task(robot_x, robot_y, robot_yaw, robot_magneto_yaw, robot_line_FL, robot_line_BL, robot_line_BR, robot_line_FR);
					robot_cmd_linX = get_home_linX();
					robot_cmd_angZ = get_home_angZ();
					robot_cmd_arm = get_home_servo();
					break;
				case SEARCH:
					opp_detected = detect_opponent();
					read_sensors(); //need to read sharp dist sensors in cm, pass it into left_sensor_dist, right_sensor_dist, mid_sensor_dist, short_sensor_dist
					task_status = search_task(robot_x, robot_y, robot_yaw, left_sensor_dist, right_sensor_dist, mid_sensor_dist, short_sensor_dist, , opp_detected)
					// task_status = COLLECT;
					// task_status = search_task(sensorA, sensorB, sensorC);
					robot_cmd_linX = search_linX();
					robot_cmd_angZ = search_angZ();
					break;
				case COLLECT:
					task_status = DELIVER;
					// task_status = collect_task(robot_x, robot_y, robot_yaw, robot_arm_position, ball_in_chamber_status, limit_switch_D);
					robot_cmd_linX = get_collect_linX();
					robot_cmd_angZ = get_collect_angZ();
					robot_cmd_arm = get_collect_servo();
					break;
				case DELIVER:
					task_status = deliver_task(robot_yaw, robot_arm_position, ball_in_chamber_status, limit_switch_D);
					robot_cmd_linX = get_deliver_linX();
					robot_cmd_angZ = get_deliver_angZ();
					robot_cmd_arm = get_deliver_servo();
					break;
			}
		}
        // end of main loop
		while (time1[T1] < DT * 1000){}
	}
}
