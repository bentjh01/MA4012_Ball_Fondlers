#ifndef MOTORS_H
#define MOTORS_H

#include "config.h"
/* _____________________________________________________________________________________________________________________

MOTORS DRIVER
_____________________________________________________________________________________________________________________ */

float calcualte_rpm_L(float linX, float angZ){
	float radian_per_sec = angZ * DEGREE_TO_RADIAN;
	// float rpmR = (linX + radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2);
	float rpmL = (linX - radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2) * RADIAN_T0_RPM;
	return rpmL ;
}

float calcualte_rpm_R(float linX, float angZ){
	float radian_per_sec = angZ * DEGREE_TO_RADIAN;
	float rpmR = (linX + radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2) * RADIAN_T0_RPM;
	// float rpmL = (linX - radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2);
	return rpmR;
}

float calculate_actual_rpm_L(float rpmR, float rpmL){
	float higher_rpm;
	if (fabs(rpmR) > fabs(rpmL)){
		higher_rpm = fabs(rpmR);
		} else {
		higher_rpm = fabs(rpmL);
	}
	if (higher_rpm == 0){
		rpmR= 0;
		rpmL = 0;
		}
	else {
		rpmR= rpmR/MAX_WHEEL_RPM * higher_rpm * RADIAN_T0_RPM;
		rpmL = rpmL/MAX_WHEEL_RPM * higher_rpm * RADIAN_T0_RPM;
	}

	return rpmL;
}

float calculate_actual_rpm_R(float rpmR, float rpmL){
	float higher_rpm;
	if (fabs(rpmR) > fabs(rpmL)){
		higher_rpm = fabs(rpmR);
		} else {
		higher_rpm = fabs(rpmL);
	}
	if (higher_rpm == 0){
		rpmR= 0;
		rpmL = 0;
		}
	else {
		rpmR= rpmR/MAX_WHEEL_RPM * higher_rpm * RADIAN_T0_RPM;
		rpmL = rpmL/MAX_WHEEL_RPM * higher_rpm * RADIAN_T0_RPM;
	}

	return rpmR;
}

float calculate_linear_x(float rpm_R, float rpm_L){
	float linX = (rpm_R + rpm_L) / RADIAN_T0_RPM * WHEEL_DIAMETER /4;
	// angZ= (rpmR - rpmL) / RADIAN_T0_RPM * WHEEL_DIAMETER/ROBOT_TRACK;
	return linX;
}

float calculate_angular_z(float rpm_R, float rpm_L){
	// float linX = (rpm_R + rpm_L) / RADIAN_T0_RPM * WHEEL_DIAMETER /4;
	float angZ = (rpm_R - rpm_L) * WHEEL_DIAMETER/ROBOT_TRACK / RADIAN_T0_RPM / DEGREE_TO_RADIAN;
	return angZ;
}

#endif // MOTORS_H