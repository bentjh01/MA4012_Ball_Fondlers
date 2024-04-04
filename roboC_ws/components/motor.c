#include "../config.h"
/* _____________________________________________________________________________________________________________________

MOTORS DRIVER
_____________________________________________________________________________________________________________________ */

/**
 * Limits the RPM (Rotations Per Minute) of the left wheel based on the RPM of the right wheel.
 * If the absolute value of the RPM of both wheels is less than or equal to MAX_WHEEL_RPM,
 * the RPM of the left wheel remains unchanged.
 * If the absolute value of the RPM of the right wheel is greater than the RPM of the left wheel,
 * the RPM of the left wheel is adjusted proportionally to reach the maximum RPM limit.
 *
 * @param rpmL The RPM of the left wheel.
 * @param rpmR The RPM of the right wheel.
 * @return The limited RPM of the left wheel.
 */
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

/**
 * Limits the RPM (Rotations Per Minute) of the right wheel based on the RPM of the left wheel.
 * If the absolute value of the RPM of both wheels is less than or equal to MAX_WHEEL_RPM,
 * the RPM of the right wheel remains unchanged.
 * If the absolute value of the RPM of the right wheel is greater than the RPM of the left wheel,
 * the RPM of the right wheel is scaled down proportionally to the RPM of the left wheel,
 * and then limited to MAX_WHEEL_RPM.
 *
 * @param rpmL The RPM of the left wheel.
 * @param rpmR The RPM of the right wheel.
 * @return The limited RPM of the right wheel.
 */
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
	rpmR = rpmR / higher_rpm * MAX_WHEEL_RPM;

	return rpmR;
}

/**
 * Limits the input power value to a range of -127 to 127.
 *
 * @param power The input power value to be limited.
 * @return The limited power value within the range of -127 to 127.
 */
int limit_byte(float power){
	if (power > 127){
		power = 127;
	} else if (power < -127){
		power = -127;
	}
	return power;
}
