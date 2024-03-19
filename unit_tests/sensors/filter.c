#include "sensors.h"

/**
 * @brief Low pass filter
 * @param input The current input value
 * @param prev_input The previous input value
 * @param cutoff The cutoff frequency
*/
float low_pass_filter(float input, float prev_input, float cutoff){
	float alpha = 1/(2*M_PI*cutoff*DT +1);
	return alpha*input + (1-alpha)*prev_input;
}