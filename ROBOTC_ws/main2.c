#include "main2.h"

/* _____________________________________________________________________________________________________________________

SUPPORT FUNCTIONS
_____________________________________________________________________________________________________________________ */

float fast_inverse_sqrt(float x) {
  // Union allows reinterpreting bits as a float
  union {
    float f;
    long i;
  } conv;

  // Initial guess using bit shift and bias adjustment
  conv.f = x;
  conv.i = 0x5f3759df - (conv.i >> 1);

  // One iteration of Newton-Raphson method for refinement
  conv.f = conv.f * (1.5f - (x * conv.f * conv.f));

  // Return the refined value
  return conv.f;
}

pid_t pid_init(float Kp, float Ki, float Kd, float setpoint) {
    pid_t pid;
    pid.Kp = Kp;
    pid.Ki = Ki;
    pid.Kd = Kd;
    pid.setpoint = setpoint;
    pid.integral = 0.0;
    pid.prev_error = 0.0;
    pid.prev_time = 0.0;
	pid.output = 0.0;
    return pid;
}

pid_t pid_update(pid_t pid, float feedback, float dt) {
    float error = pid.setpoint - feedback; 
    float derivative = (error - pid.prev_error) / dt;
	pid.integral += error * dt;
    pid.output = pid.Kp * error + pid.Ki * pid.integral + pid.Kd * derivative;
    pid.prev_error = error;
    // pid.prev_time = millis()/1000;
    return pid;
}

/* _____________________________________________________________________________________________________________________

MOTORS
_____________________________________________________________________________________________________________________ */

motor_rpm_t calcualte_rpm(twist_t twist){
	motor_rpm_t rpm;
	float radian_per_sec = twist.angular_z * DEGREE_TO_RADIAN;
	rpm.right = (twist.linear_x + radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2);
	rpm.left = (twist.linear_x - radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2);
	return rpm;
}

motor_rpm_t calculate_actual_rpm(motor_rpm_t rpm){
	float higher_rpm;
	if (rpm.right > rpm.left){
		higher_rpm = rpm.right;
	} else {
		higher_rpm = rpm.left;
	}
	rpm.right= rpm.right/higher_rpm * MAX_WHEEL_RPM;
	rpm.left = rpm.left/higher_rpm * MAX_WHEEL_RPM;
	return rpm;
}

twist_t calculate_actual_twist(motor_rpm_t rpm){
	twist_t twist;
	twist.linear_x = (rpm.right + rpm.left) * WHEEL_DIAMETER/4;
	twist.angular_z = (rpm.right - rpm.left) * WHEEL_DIAMETER/ROBOT_TRACK;
	return twist;
}

void robot_move(motor_rpm_t rpm){
	int motor_power_R = rpm.right/MAX_WHEEL_RPM * 127;
	int motor_power_L = rpm.left/MAX_WHEEL_RPM * 127;
	motor[wheel_R] = motor_power_R;
	motor[wheel_L] = motor_power_L;
}

/* _____________________________________________________________________________________________________________________

ROBOT STATE
_____________________________________________________________________________________________________________________ */

pose_t init_robot_pose(void){
	pose_t pose;
	pose.x = 0;
	pose.y = 0;
	pose.yaw = 0;
	pose.linear_x = 0;
	pose.angular_z = 0;
	return pose;
}

pose_t predict_state_model(pose_t last_pose, twist_t cmd_vel, float dt) {
    pose_t estimated_pose;
    estimated_pose.x = last_pose.x + last_pose.x * dt * cos(last_pose.yaw);
    estimated_pose.y = last_pose.y + last_pose.x * dt * sin(last_pose.yaw);
    estimated_pose.yaw = last_pose.yaw + last_pose.angular_z * dt;
    estimated_pose.linear_x = cmd_vel.linear_x;
    estimated_pose.angular_z = cmd_vel.angular_z;
    return estimated_pose;
}

pose_t predict_state_encoders(pose_t last_pose, encoder_count_t new_en_count, encoder_count_t old_en_count, float dt) {
    pose_t estimated_pose;
    int d_en_right = new_en_count.right - old_en_count.right;
    int d_en_left = new_en_count.left - old_en_count.left;
    // Simple robot model
	float drad_right = d_en_right / ENCODER_RESOLUTION * 2 * M_PI;
	float drad_left = d_en_left / ENCODER_RESOLUTION * 2 * M_PI;

	float dx = (drad_right + drad_left) * WHEEL_DIAMETER / 4 * cos(last_pose.yaw);
	float dy = (drad_right + drad_left) * WHEEL_DIAMETER / 4 * sin(last_pose.yaw);
	float dyaw = (drad_right - drad_left) * WHEEL_DIAMETER / ROBOT_TRACK;

    estimated_pose.x = last_pose.x + dx;
    estimated_pose.y = last_pose.y + dy;
    estimated_pose.yaw = last_pose.yaw + dyaw;
    estimated_pose.linear_x = fast_inverse_sqrt(dx*dx + dy*dy) / dt;
    estimated_pose.angular_z = dyaw / dt;
    return estimated_pose;
}

pose_t ab_filter_update(pose_t last_pose, twist_t cmd_vel, encoder_count_t new_en_count, encoder_count_t old_en_count, float dt){
	pose_t pose;
    pose_t predicted_pose = predict_state_model(last_pose, cmd_vel, dt);
    pose_t encoder_pose = predict_state_encoders(last_pose, new_en_count, old_en_count, dt);

    float encoder_x_innovation = encoder_pose.x - predicted_pose.x;
    float encoder_y_innovation = encoder_pose.y - predicted_pose.y;
    float encoder_yaw_innovation = encoder_pose.yaw - predicted_pose.yaw;
    float encoder_linear_velocity_innovation = encoder_pose.linear_x - predicted_pose.linear_x;
    float encoder_angular_velocity_innovation = encoder_pose.angular_z - predicted_pose.angular_z;

    pose.x = predicted_pose.x + ENCODER_FILTER_GAIN * encoder_x_innovation;
    pose.y = predicted_pose.y + ENCODER_FILTER_GAIN * encoder_y_innovation;
    pose.yaw = predicted_pose.yaw + ENCODER_FILTER_GAIN * encoder_yaw_innovation;
    pose.linear_x = predicted_pose.linear_x + ENCODER_FILTER_GAIN * encoder_linear_velocity_innovation;
    pose.angular_z = predicted_pose.angular_z + ENCODER_FILTER_GAIN * encoder_angular_velocity_innovation;

    return pose;
}

/* _____________________________________________________________________________________________________________________

GLOBAL VARIABLES
_____________________________________________________________________________________________________________________ */

int line_FL_val;
int line_BL_val;
int line_BR_val;
int	line_FR_val;

int dis_L_val;
int dis_R_val;
int dis_mid_val;

int dis_top_val;

int last_enR;
int last_enL;
int enR;
int enL;

int task_state = 1;

twist_t robot_twist;
float robot_linear_x;
float robot_angular_z;

motor_rpm_t robot_rpm;
float robot_rpm_R;
float robot_rpm_L;

pose_t robot_pose;

pid_t delivery_pid;
pid_t home_pid;

/* _____________________________________________________________________________________________________________________

SENSORS
_____________________________________________________________________________________________________________________ */

void read_sensors(){
	line_FL_val = SensorValue[line_FL];
	line_BL_val = SensorValue[line_BL];
	line_BR_val = SensorValue[line_BR];
	line_FR_val = SensorValue[line_FR];

	dis_L_val = SensorValue[long_distance_L];
	dis_R_val = SensorValue[long_distance_R];
	dis_mid_val = SensorValue[short_distance];

	dis_top_val = SensorValue[long_distance_top];

	last_enR = enR;
	last_enL = enL;
	enR = getMotorEncoder[motor_R];
	enL = getMotorEncoder[motor_L];
}

void update_pose(){
	robot_pose = ab_filter_update(robot_pose, robot_twist, (encoder_count_t){enR, enL}, (encoder_count_t){last_enR, last_enL}, 0.05);
}

/* _____________________________________________________________________________________________________________________

TASKS
_____________________________________________________________________________________________________________________ */


int edge_detected(){
	if (line_FL_val > LINE_SENSOR_THRESHOLD){
		return 1;
	} else {
		return 0;
	}
	if (line_BL_val > LINE_SENSOR_THRESHOLD){
		return 1;
	} else {
		return 0;
	}
	if (line_BR_val > LINE_SENSOR_THRESHOLD){
		return 1;
	} else {
		return 0;
	}
	if (line_FR_val > LINE_SENSOR_THRESHOLD){
		return 1;
	} else {
		return 0;
	}
}

int edge_avoid(){
	robot_rpm = (motor_rpm_t){0,0};
	robot_move(robot_rpm);
	return 1;
}

int home(){
	int sucess = 0;
	twist_t twist;
	motor_rpm_t rpm;
	if (robot_pose.x <= 0.8 && robot_pose.y <= 0.6){
		twist.linear_x  = MAX_SPEED;
		home_pid.setpoint = 0.6;
		home_pid = pid_update(home_pid, robot_pose.y, 0.05);
		twist.angular_z = home_pid.output;

		rpm =  calcualte_rpm(twist);
		rpm = calculate_actual_rpm(rpm);
		twist = calculate_actual_twist(rpm);
		robot_move(rpm);
	} else {
		robot_move((motor_rpm_t){0,0});
		sucess = 1;
	}
	return 2;
}

int search_ball(){
	return 3;
}

int goto_ball(){
	return 4;
}

int grab_ball(){
	return 5;
}

int deliver_ball(){
	int sucess = 0;
	twist_t twist;
	motor_rpm_t rpm;
	if (1){ // Check if ball is in the robot and if the robot is in the delivery area
		twist.linear_x  = MAX_SPEED;
		delivery_pid = pid_update(delivery_pid, robot_pose.yaw, 0.05);
		twist.angular_z = delivery_pid.output;

		rpm =  calcualte_rpm(twist);
		rpm = calculate_actual_rpm(rpm);
		twist = calculate_actual_twist(rpm);
		robot_move(rpm);
		// FOR TESTING
		robot_linear_x = twist.linear_x;
		robot_angular_z = twist.angular_z;
		robot_rpm_R = rpm.right;
		robot_rpm_L = rpm.left;
	} else {
		robot_move((motor_rpm_t){0,0});
		sucess = 1;
	}

	if (sucess){
		return 1;
	} else {
		return 5;
	}
}

task main()
{
	float dt = 0.05;
	robot_pose = init_robot_pose();
	delivery_pid = pid_init(delivery_pid_kp, delivery_pid_ki, delivery_pid_kd, 0);
	home_pid = pid_init(1, 0, 0, 0);
	while(1){
		clearTimer(T1);
		// Main Loop
		read_sensors();
		update_pose();
		if (edge_detected()){
			// Stop
			robot_move((motor_rpm_t){0,0});
		} else {
			switch (task_state)
			{
			case HOME:
				task_state = home();

			case SEARCH_BALL:
				task_state = search_ball();

			case GOTO_BALL:
				task_state = goto_ball();

			case GRAB_BALL:
				task_state = grab_ball();

			case DELIVER_BALL:
				task_state = deliver_ball();

			default:
				task_state = search_ball();
			}
			robot_move(robot_rpm);
		}

		while (time1[T1] < 1/dt){}
	}
}


