#include "odom_test.h"

/**
 * @brief Performs modulo operation x/y
 * @param numerator the numerator of the operation i.e. x
 * @param denominator the denominator of the operation i.e. y
 * @return the remainder of the division operation.
*/
float modulo(float numerator, float denominator){
    return (numerator/denominator - round(numerator/denominator)) * denominator;
}

/**
 * @brief Wraps the angle from -180 to 180 degrees wrt to the X-Axis i.e. negative angles are CW and positive are CCW
 * @param angle angle to wrap in DEG. MUST be less than +/-360 DEG
 * @return angle from -180 to 180 DEG
*/
float wrap_to_pi(float angle){
	if (angle == 180){
		return -180.0;
	}
	if (fabs(angle) > 180.0){
		return (sgn(angle) * (fabs(angle) - 360.0));
	}
	return angle;
}

/**
 * @brief Fast inverse square root. Trust Trust if not then do refer online on how it works cuz it makes no sense when you read it. 
 * @param x value to squareroot
 * @return square root of x
*/
float fast_inverse_sqrt(float x) {
	// Initial estimate based on bit manipulation (common for fast inverse sqrt)
	float xhalf = 0.5 * x;
	int i = *(int*) &x;  // reinterpret cast to int, not recommended for portability
	i = 0x5f355f8b - (i >> 1);  // Adjust the initial guess based on MSB of float

	// Iterate a few times using Newton-Raphson method for refinement
	float y = xhalf;
	for (int n = 0; n < 4; n++) {
		y = y * (1.5 - (x * y * y));
	}
	return y;
}

/**
 * @brief Low pass filter
 * @param input The current input value
 * @param prev_input The previous input value
 * @param alpha The cutoff frequency 0 < alpha < 1
*/
float low_pass_filter(float input, float prev_input, float alpha){
	return alpha*input + (1-alpha)*prev_input;
}

/**
 * @brief Discretise the yaw reading into bins of 45 [deg] each
 * @param yaw the yaw reading to discretise
 * @return the discretised yaw valies in 45 [deg] increments
*/
float discretise_yaw(float yaw){
    return round(yaw / 45) * 45;
}