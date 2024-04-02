#ifndef MOTORS_H
#define MOTORS_H

#include "../config.h"
/* _____________________________________________________________________________________________________________________

MOTORS DRIVER
_____________________________________________________________________________________________________________________ */

float calcualte_rpmL(float linX, float angZ){
	float radian_per_sec = angZ * DEGREE_TO_RADIAN;
	float rpmL = (linX - radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2) * RADIAN_T0_RPM;
	return rpmL;
}

float calcualte_rpmR(float linX, float angZ){
	float radian_per_sec = angZ * DEGREE_TO_RADIAN;
	float rpmR = (linX + radian_per_sec*ROBOT_TRACK/2)/(WHEEL_DIAMETER/2) * RADIAN_T0_RPM;
	return rpmR;
}

float limit_rpmL(float rpmL, float rpmR){
	if (fabs(rpmR) <= MAX_WHEEL_RPM && fabs(rpmL) <= MAX_WHEEL_RPM){
		return rpmL;
		}
	float higher_rpm;
	if (fabs(rpmR) > fabs(rpmL)){
		higher_rpm = fabs(rpmR);
		} else {
		higher_rpm = fabs(rpmL);
	}
	rpmL = rpmL/ higher_rpm * MAX_WHEEL_RPM;

	return rpmL;
}

// Limits the rpm to the maximum wheel rpm not by cutoff but by scaling
float limit_rpmR(float rpmL, float rpmR){
	if (fabs(rpmR) <= MAX_WHEEL_RPM && fabs(rpmL) <= MAX_WHEEL_RPM){
		return rpmR;
		}
	float higher_rpm;
	if (fabs(rpmR) > fabs(rpmL)){
		higher_rpm = fabs(rpmR);
		} else {
		higher_rpm = fabs(rpmL);
	}
	rpmR= rpmR/ higher_rpm * MAX_WHEEL_RPM;

	return rpmR;
}

float calculate_linear_x(float rpmL, float rpmR){
	float linX = (rpmR + rpmL) / RADIAN_T0_RPM * WHEEL_DIAMETER /4;
	return linX;
}

float calculate_angular_z(float rpmL, float rpmR){
	float angZ = (rpmR - rpmL) * WHEEL_DIAMETER/2 /ROBOT_TRACK / RADIAN_T0_RPM / DEGREE_TO_RADIAN;
	return angZ;
}

// Cut off the power if above 127 or below -127
int limit_byte(float power){
	if (power > 127){
		power = 127;
		} else if (power < -127){
		power = -127;
	}
	return power;
}

#endif // MOTORS_H