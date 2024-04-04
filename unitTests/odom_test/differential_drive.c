#include "odom_test.h"

/**
 * Calculates the linear velocity in the x-direction based on the RPM of the left and right wheels.
 *
 * @param rpmL The RPM of the left wheel.
 * @param rpmR The RPM of the right wheel.
 * @return The linear velocity in the x-direction.
 */
float calculate_linear_x(float rpmL, float rpmR){
	float linX =(rpmR + rpmL) / RADIAN_T0_RPM * WHEEL_DIAMETER / 4.0; 
	return linX;
}

/**
 * Calculates the angular velocity in the z-direction based on the RPM of the left and right wheels.
 *
 * @param rpmL The RPM of the left wheel.
 * @param rpmR The RPM of the right wheel.
 * @return The angular velocity in the z-direction.
 */
float calculate_angular_z(float rpmL, float rpmR){
	float angZ = radiansToDegrees((rpmR - rpmL) * WHEEL_DIAMETER / ROBOT_TRACK / RADIAN_T0_RPM / 2.0);
	return angZ;
}

/**
 * Calculates the RPM of the left wheel based on the desired linear velocity and angular velocity.
 *
 * @param linX The desired linear velocity.
 * @param angZ The desired angular velocity.
 * @return The RPM of the left wheel.
 */
float calculate_rpmL(float linX, float angZ){
	// float radian_per_sec = degreesToRadians(angZ);
	float radian_per_sec = angZ * DEGREE_TO_RADIAN;
	float rpmL = (linX - radian_per_sec * ROBOT_TRACK / 2.0) / (WHEEL_DIAMETER / 2.0) * RADIAN_T0_RPM;
	return rpmL;
}

/**
 * Calculates the RPM of the right wheel based on the desired linear velocity and angular velocity.
 *
 * @param linX The desired linear velocity.
 * @param angZ The desired angular velocity.
 * @return The RPM of the right wheel.
 */
float calculate_rpmR(float linX, float angZ){
	// float radian_per_sec = degreesToRadians(angZ);
	float radian_per_sec = angZ * DEGREE_TO_RADIAN;
	float rpmR = (linX + radian_per_sec * ROBOT_TRACK / 2.0) / (WHEEL_DIAMETER / 2.0) * RADIAN_T0_RPM;
	return rpmR;
}