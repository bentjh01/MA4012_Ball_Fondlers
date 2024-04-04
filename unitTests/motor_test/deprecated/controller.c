#include "motor_test.h"

// PID Controller for the right motor
float pid_R(float setpointR, float en_rpmR, float bias){
    static float motor_R_integral = 0;
    static float motor_R_prev_error = 0;
    float error = setpointR - en_rpmR;
    motor_R_integral = motor_R_integral + error * DT;
    float derivative = (error - motor_R_prev_error) / DT;
    float output = MOTOR_R_KP * error + MOTOR_R_KI * motor_R_integral + MOTOR_R_KD * derivative + bias;
    motor_R_prev_error = error;
    return output;
}

// PID Controller for the left motor
float pid_L(float setpointL, float en_rpmL, float bias){
    static float motor_L_integral = 0;
    static float motor_L_prev_error = 0;
    float error = setpointL - en_rpmL;
    motor_L_integral = motor_L_integral + error * DT;
    float derivative = (error - motor_L_prev_error) / DT;
    float output = MOTOR_L_KP * error + MOTOR_L_KI * motor_L_integral + MOTOR_L_KD * derivative + bias;
    motor_L_prev_error = error;
    return output;
}

// We can use an energy balance equation to get a rough estimate of the byte value of the motor power.