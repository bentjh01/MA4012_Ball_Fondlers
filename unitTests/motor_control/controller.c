#include "config.h"

float motor_R_integral = 0;
float motor_R_prev_error = 0;

float motor_L_integral = 0;
float motor_L_prev_error = 0;

// PID Controller for the right motor
float pid_R(float rpmR, float setpointR){
    float error = setpointR - rpmR;
    motor_R_integral = motor_R_integral + error * DT;
    float derivative = (error - motor_R_prev_error) / DT;
    float output = MOTOR_R_KP * error + MOTOR_R_KI * motor_R_integral + MOTOR_R_KD * derivative;
    motor_R_prev_error = error;
    return output;
}

// PID Controller for the left motor
float pid_L(float rpmL, float setpointL){
    float error = setpointL - rpmL;
    motor_L_integral = motor_L_integral + error * DT;
    float derivative = (error - motor_L_prev_error) / DT;
    float output = MOTOR_L_KP * error + MOTOR_L_KI * motor_L_integral + MOTOR_L_KD * derivative;
    motor_L_prev_error = error;
    return output;
}

// We can use an energy balance equation to get a rough estimate of the byte value of the motor power.