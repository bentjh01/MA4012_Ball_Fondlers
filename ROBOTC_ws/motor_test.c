#include "pinout.c"
#include "config.h"

typedef struct {
    float linear_x;
    float angular_z;
} twist_t;

typedef struct {
    int left;
    int right;
} motor_rpm_t;  

/* _____________________________________________________________________________________________________________________

MOTORS
_____________________________________________________________________________________________________________________ */

void calcualte_rpm(twist_t twist, motor_rpm_t &rpm){
	float radian_per_sec = twist.angular_z * DEGREE_TO_RADIAN;
	rpm.right = (twist.linear_x + radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2);
	rpm.left = (twist.linear_x - radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2);
	return;
}

void calculate_actual_rpm(motor_rpm_t &rpm){
	float higher_rpm;
	if (rpm.right > rpm.left){
		higher_rpm = rpm.right;
		} else {
		higher_rpm = rpm.left;
	}
	if (higher_rpm == 0){
		rpm.right= 0;
		rpm.left = 0;
	} else{
		rpm.right= rpm.right/higher_rpm * MAX_WHEEL_RPM;
		rpm.left = rpm.left/higher_rpm * MAX_WHEEL_RPM;
	}

	return;
}

void calculate_actual_twist(motor_rpm_t rpm, twist_t &twist){
	twist.linear_x = (rpm.right + rpm.left) * WHEEL_DIAMETER/4;
	twist.angular_z = (rpm.right - rpm.left) * WHEEL_DIAMETER/ROBOT_TRACK;
	return;
}

void robot_move(motor_rpm_t rpm){
	int motor_power_R = rpm.right/MAX_WHEEL_RPM * 127;
	int motor_power_L = rpm.left/MAX_WHEEL_RPM * 127;
	motor[motor_R] = motor_power_R;
	motor[motor_L] = motor_power_L;
}

twist_t robot_twist = {0, 0};
motor_rpm_t robot_rpm = {0, 0};

void motor_test(){
    twist_t twist;
    motor_rpm_t rpm;
    twist.linear_x = 0;
    twist.angular_z = 0;
    calcualte_rpm(twist, rpm);
    calculate_actual_rpm(rpm);
    calculate_actual_twist(rpm, twist);
    robot_move(rpm);
    robot_twist = twist;
    robot_rpm = rpm;
}

task main()
{
	resetMotorEncoder(motor_R);
	resetMotorEncoder(motor_L);
	while(1){
		clearTimer(T1);
        read_sensors();
		// Main Loop
		
        motor_test();

		while (time1[T1] < DT * 1000){}
		update_pose();
	}
}