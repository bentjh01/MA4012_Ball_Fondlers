#include "config.h"

float motor_R_Kp = 0.588671875;
float motor_R_Ki = 0.0;
float motor_R_Kd = 0.0;
float motor_R_integral = 0;
float motor_R_prev_error = 0;

float motor_L_Kp = 0.0;
float motor_L_Ki = 0.0;
float motor_L_Kd = 0.0;
float motor_L_integral = 0;
float motor_L_prev_error = 0;


float pid_R(float rpmR, float setpointR){
    float error = setpointR - rpmR;
    motor_R_integral = motor_R_integral + error * DT;
    float derivative = (error - motor_R_prev_error) / DT;
    float output = motor_R_Kp * error + motor_R_Ki * motor_R_integral + motor_R_Kd * derivative;
    motor_R_prev_error = error;
    return output;
}

float pid_L(float rpmL, float setpointL){
    float error = setpointL - rpmL;
    motor_L_integral = motor_L_integral + error * DT;
    float derivative = (error - motor_L_prev_error) / DT;
    float output = motor_L_Kp * error + motor_L_Ki * motor_L_integral + motor_L_Kd * derivative;
    motor_L_prev_error = error;
    return output;
}