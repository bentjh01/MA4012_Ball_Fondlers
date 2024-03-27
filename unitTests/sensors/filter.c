#include "sensors.h"

/**
 * @brief Low pass filter
 * @param input The current input value
 * @param prev_input The previous input value
 * @param alpha The cutoff frequency 0 < alpha < 1
*/
float low_pass_filter(float input, float prev_input, float alpha){
	return alpha*input + (1-alpha)*prev_input;
}