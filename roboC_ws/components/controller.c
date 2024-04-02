#include "../config.h"

static float motor_R_integral = 0;
static float motor_R_prev_error = 0;

static float motor_L_integral = 0;
static float motor_L_prev_error = 0;

// RPM to POWER conversion
float rpm_to_power(float rpm){
    if (rpm == 0) return 0;
    return sgn(rpm) * RPM_GAIN * pow(E, EXPONENT_GAIN * fabs(rpm));
}

// PID Controller for the right motor
float pid_R(float setpointR, float en_rpmR){
    float error = setpointR - en_rpmR;
    motor_R_integral = motor_R_integral + error * DT;
    float derivative = (error - motor_R_prev_error) / DT;
    float bias = rpm_to_power(setpointR);
    float output = MOTOR_R_KP * error + MOTOR_R_KI * motor_R_integral + MOTOR_R_KD * derivative + bias;
    motor_R_prev_error = error;
    return output;
}

// PID Controller for the left motor
float pid_L(float setpointL, float en_rpmL){
    float error = setpointL - en_rpmL;
    motor_L_integral = motor_L_integral + error * DT;
    float derivative = (error - motor_L_prev_error) / DT;
    float bias = rpm_to_power(setpointL);
    float output = MOTOR_L_KP * error + MOTOR_L_KI * motor_L_integral + MOTOR_L_KD * derivative + bias;
    motor_L_prev_error = error;
    return output;
}

// We can use an energy balance equation to get a rough estimate of the byte value of the motor power.