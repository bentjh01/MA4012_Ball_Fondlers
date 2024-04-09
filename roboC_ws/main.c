#pragma config(Sensor, in1,    long_distance_R_pin, sensorAnalog)
#pragma config(Sensor, in2,    long_distance_M_pin, sensorAnalog)
#pragma config(Sensor, in3,    long_distance_L_pin, sensorAnalog)
#pragma config(Sensor, in4,    short_distance_T_pin, sensorAnalog)
#pragma config(Sensor, in5,    line_BR_pin,    sensorAnalog)
#pragma config(Sensor, in6,    line_FR_pin,    sensorAnalog)
#pragma config(Sensor, in7,    line_FL_pin,    sensorAnalog)
#pragma config(Sensor, in8,    line_BL_pin,    sensorAnalog)
#pragma config(Sensor, dgtl1,  wheel_L_encoderA_pin, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  wheel_R_encoderA_pin, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  limit_switch_A_pin, sensorDigitalIn)
#pragma config(Sensor, dgtl6,  limit_switch_B_pin, sensorDigitalIn)
#pragma config(Sensor, dgtl7,  limit_switch_C_pin, sensorDigitalIn)
#pragma config(Sensor, dgtl8,  limit_switch_D_pin, sensorDigitalIn)
#pragma config(Sensor, dgtl9,  magneto_west_pin, sensorDigitalIn)
#pragma config(Sensor, dgtl10, magneto_south_pin, sensorDigitalIn)
#pragma config(Sensor, dgtl11, magneto_east_pin, sensorDigitalIn)
#pragma config(Sensor, dgtl12, magneto_north_pin, sensorDigitalIn)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           motor_R,       tmotorVex393_MC29, openLoop, encoderPort, dgtl3)
#pragma config(Motor,  port7,           motor_L,       tmotorVex393_MC29, openLoop, reversed, encoderPort, dgtl1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "config.h"
#include "components/components.h"
#include "robotTasks/robotTasks.h"
/* _____________________________________________________________________________________________________________________

GLOBAL VARIABLES
_____________________________________________________________________________________________________________________ */

// Robot State
float robot_x = 0.0;
float robot_y = 0.0;
float robot_yaw = 0;
float robot_linX = 0;
float robot_angZ = 0.0;

float robot_arm_position = 0.0;

// robot twist
float robot_cmd_rpmR = 0.0;
float robot_cmd_rpmL = 0.0;
float robot_cmd_linX = 0.0;
float robot_cmd_angZ = 0.0;

float robot_cmd_arm_position = 0.0;
float robot_arm_direction = 0.0;

// robot encoders
float robot_en_rpmR = 0.0;
float robot_en_rpmL = 0.0;
float robot_en_linX = 0.0;
float robot_en_angZ = 0.0;

// magnetometer
float magnetometer_yaw = 0.0;

// robot line sensors
int robot_line_FL = 0;
int robot_line_BL = 0;
int robot_line_BR = 0;
int robot_line_FR = 0;

// robot distance sensors
float distance_sensor_left = 0.0;
float distance_sensor_right = 0.0;
float distance_sensor_top = 0.0;
float distance_sensor_mid = 0.0;

// limit siwtches
int limit_switch_A = 0;
int limit_switch_B = 0;
int limit_switch_C = 0;
int limit_switch_D = 0;

// robot task
int task_status = HOME;
int prev_task_status = HOME;

// opponent detection
int opp_detected;

// ball status
int ball_in_chamber_status;
int ball_detected;
float ball_x_memory;
float ball_y_memory;
float ball_yaw_memory;
/* _____________________________________________________________________________________________________________________

SENSORS
_____________________________________________________________________________________________________________________ */
void read_sensors(float dt){
    magnetometer_yaw = read_compass(SensorValue[magneto_north_pin], SensorValue[magneto_south_pin], SensorValue[magneto_east_pin], SensorValue[magneto_west_pin]);
    magnetometer_yaw = wrap_to_pi(magnetometer_yaw - MAGNETOMETER_OFFSET);

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

    robot_en_rpmL = filter_encoderL(getMotorEncoder(motor_L) * 60.0/dt /ENCODER_RESOLUTION);
	robot_en_rpmR = filter_encoderR(getMotorEncoder(motor_R) * 60.0/dt /ENCODER_RESOLUTION);

	resetMotorEncoder(motor_R);
	resetMotorEncoder(motor_L);
	return;
}

void check_for_ball(){
	ball_detected = detect_ball(distance_sensor_left, distance_sensor_right, distance_sensor_mid, opp_detected);
	if (ball_detected == TRIGGERED){
		ball_x_memory = robot_x;
		ball_y_memory = robot_y;
		ball_yaw_memory = robot_yaw;
	}
	return;
}

void update_robot_odom(float dt){
    robot_x = update_odometry_x(robot_x, robot_yaw, robot_linX, robot_en_rpmL, robot_en_rpmR, dt);
    robot_y = update_odometry_y(robot_y, robot_yaw, robot_linX, robot_en_rpmL, robot_en_rpmR, dt);
    robot_yaw = update_odometry_yaw(robot_yaw, robot_angZ, robot_en_rpmL, robot_en_rpmR, magnetometer_yaw, dt);
    // robot_yaw = magnetometer_yaw;
    robot_linX = update_odometry_linX(robot_linX, robot_en_rpmL, robot_en_rpmR, dt);
    robot_angZ = update_odometry_angZ(robot_cmd_angZ, robot_en_rpmL, robot_en_rpmR, dt);
    return;
}

void robot_execute(float dt){
	robot_cmd_rpmL = calculate_rpmL(robot_cmd_linX, robot_cmd_angZ);
	robot_cmd_rpmR = calculate_rpmR(robot_cmd_linX, robot_cmd_angZ);
	robot_cmd_rpmL = limit_rpmL(robot_cmd_rpmL, robot_cmd_rpmR);
	robot_cmd_rpmR = limit_rpmR(robot_cmd_rpmL, robot_cmd_rpmR);
	robot_move_closed(robot_cmd_rpmL, robot_cmd_rpmR, robot_en_rpmL, robot_en_rpmR);
	robot_cmd_linX = calculate_linear_x(robot_cmd_rpmL, robot_cmd_rpmR);
	robot_cmd_angZ = calculate_angular_z(robot_cmd_rpmL, robot_cmd_rpmR);

	robot_arm_position = get_arm_position(robot_arm_position, robot_cmd_arm_position , robot_arm_direction, limit_switch_A, limit_switch_B, limit_switch_C);
	robot_arm_direction = robot_arm_move(robot_cmd_arm_position, robot_arm_position);
	return;
}

/* _____________________________________________________________________________________________________________________

TASKS
_____________________________________________________________________________________________________________________ */

/**
 * @brief Initialises the robot
*/
void init_robot(){
	robot_x = 0.0;
	robot_y = 0.0;
	robot_yaw = 0.0;
	robot_linX = 0.0;
	robot_angZ = 0.0;
	robot_cmd_linX = 0.0;
	robot_cmd_angZ = 0.0;
	robot_arm_position = SWITCH_C_POSITION;
	task_status = HOME;
}

void wait_to_go(){
	int ready = 0;
	while (ready != 1){
		int limit_state = SensorValue[limit_switch_C_pin];
		if (limit_state == TRIGGERED){
			while(1){
				sleep(10);
				init_robot();
				limit_state = SensorValue[limit_switch_C_pin];
				if (limit_state == NOT_TRIGGERED){
					ready = 1;
					break;
				}
			}
		}
	}
	return;
}

task robot_read(){
	while(1){
		clearTimer(T2);
		read_sensors(DT_READ);
		check_for_ball();
		update_robot_odom(DT_READ);
        robot_execute(DT_READ);
		while (time1[T2] < DT_READ * 1000){}
	}
}

task main()
{
	wait_to_go();
	startTask(robot_read);
	while(1){
		clearTimer(T1);
		// main Loop
		if (edge_detected(robot_line_FL, robot_line_BL, robot_line_BR, robot_line_FR) == TRIGGERED){
		// if (1 == 2){
			if(task_status == DELIVER && fabs(robot_yaw) < YAW_TOLERANCE){
				int line_case = get_edge_line_case();
				if (line_case == 1001){
					task_status = DELIVER;
				}
				else if (line_case == 1101 || line_case == 1011){
					if (robot_x <= 0.05){
						task_status = DELIVER;
					}
				}
			}

			if (task_status != EDGE){
				prev_task_status = task_status;
			}

			else{
				task_status = EDGE;
			}
			avoid_case_check(robot_x, robot_y, robot_yaw, robot_line_FL, robot_line_FR, robot_line_BL, robot_line_BR);
			// wall_case_check(robot_yaw, robot_line_FL, robot_line_FR, robot_line_BL, robot_line_BR); @Unizz20
		}
		switch (task_status){
			case EDGE:
				task_status = edge_avoid_task(robot_x, robot_y, robot_yaw, prev_task_status);
				robot_cmd_linX = get_edge_avoid_linX();
				robot_cmd_angZ = get_edge_avoid_angZ();
				// task_status = HOME; // testing
				break;
			case HOME:
				// task_status = SEARCH;
				task_status = home_task(robot_x, robot_y, robot_yaw, robot_arm_position);
				robot_cmd_linX = get_home_linX();
				robot_cmd_angZ = get_home_angZ();
				robot_cmd_arm_position = get_home_servo();
				break;
			case SEARCH:
				// opp_detected = opponent_detection(distance_sensor_top);
				task_status = GOTO;
				// task_status = search_task(robot_x, robot_y, robot_yaw, distance_sensor_left, distance_sensor_right, distance_sensor_mid, opp_detected, robot_en_rpmL, robot_en_rpmR);
				// task_status = search_task_alt(ball_detected);
				// robot_cmd_linX = get_search_linX();
				// robot_cmd_angZ = get_search_angZ();
				break;
			case GOTO:
				// opp_detected = opponent_detection(distance_sensor_top);
				task_status = COLLECT;
				// task_status = goto_task(robot_x, robot_y, robot_yaw, distance_sensor_left, distance_sensor_right, distance_sensor_mid, opp_detected, ball_yaw);
				// robot_cmd_linX = get_goto_linX();
				// robot_cmd_angZ = get_goto_angZ();
				break;
			case COLLECT:
				task_status = DELIVER;
				// task_status = collect_task(robot_x, robot_y, robot_yaw, robot_arm_position, ball_in_chamber_status, limit_switch_D);
				// robot_cmd_linX = get_collect_linX();
				// robot_cmd_angZ = get_collect_angZ();
				// robot_cmd_arm_position = get_collect_servo();
				break;
			case DELIVER:
				// task_status = HOME;
				task_status = deliver_task(robot_yaw, robot_arm_position, ball_in_chamber_status, limit_switch_D, robot_line_BR, robot_line_BL);
				robot_cmd_linX = get_deliver_linX();
				robot_cmd_angZ = get_deliver_angZ();
				robot_cmd_arm_position = get_deliver_servo();
				if (get_reset_x() == TRIGGERED){
					robot_x = 0.0;
				}
				break;
		}
        // end of main loop
		while (time1[T1] < DT_MAIN * 1000){}
	}
}
