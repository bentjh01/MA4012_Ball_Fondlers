#include "../config.h"

float pid_L(float setpoint, float feedback, float bias){
	static float i_outL;
	static float previous_errorL;
	float error = setpoint - feedback;
	float k_out = MOTOR_L_KP * error;
	float i = i_outL + error * MOTOR_L_KI;
	if ( fabs(i) <= MOTOR_L_INTEGRAL_MAX){
		i_outL += MOTOR_L_KI * error;
	}
	float d_out = error - previous_errorL;
	float out = k_out + i_outL + d_out + bias;
	previous_errorL = error;
	if (fabs(out) >= MAX_POWER){
		return sgn(out) * MAX_POWER;
	}
	return out;
}

float pid_R(float setpoint, float feedback, float bias){
	static float i_outR;
	static float previous_errorR;
	float error = setpoint - feedback;
	float k_out = MOTOR_R_KP * error;
	float i = i_outR + error * MOTOR_R_KI;
	if (fabs(i) <= MOTOR_R_INTEGRAL_MAX){
		i_outR += MOTOR_R_KI * error;
	}
	float d_out = MOTOR_R_KD * (error - previous_errorR);
	float out = k_out + i_outR + d_out + bias;
	previous_errorR = error;
	if (fabs(out) >= MAX_POWER){
		return sgn(out) * MAX_POWER;
	}
	return out;
}