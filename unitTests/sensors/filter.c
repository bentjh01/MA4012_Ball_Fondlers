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
static float prev_line_FL_val;
static float prev_line_BL_val;
static float prev_line_BR_val;
static float prev_line_FR_val;


static float prev_dis_L_val;
static float prev_dis_R_val;
static float prev_dis_mid_val;
static float prev_dis_top_val;

float filter_line_FL(float input){
	prev_line_FL_val = input;
	return low_pass_filter(input, prev_line_FL_val, FILTER_GAIN_LINE_FL);
}
float filter_line_BL(float input){
	prev_line_BL_val = input;
	return low_pass_filter(input, prev_line_BL_val, FILTER_GAIN_LINE_BL);
}
float filter_line_BR(float input){
	prev_line_BR_val = input;
	return low_pass_filter(input, prev_line_BR_val, FILTER_GAIN_LINE_BR);
}
float filter_line_FR(float input){
	prev_line_FR_val = input;
	return low_pass_filter(input, prev_line_FR_val, FILTER_GAIN_LINE_FR);
}

float filter_distance_L(float input){
	prev_dis_L_val = input;
	return low_pass_filter(input, prev_dis_L_val, FILTER_GAIN_LONG_L);
}
float filter_distance_R(float input){
	prev_dis_R_val = input;
	return low_pass_filter(input, prev_dis_R_val, FILTER_GAIN_LONG_R);
}
float filter_distance_mid(float input){
	prev_dis_mid_val = input;
	return low_pass_filter(input, prev_dis_mid_val, FILTER_GAIN_LONG_MID);
}
float filter_distance_top(float input){
	prev_dis_top_val = input;
	return low_pass_filter(input, prev_dis_top_val, FILTER_GAIN_SHORT_TOP);
}