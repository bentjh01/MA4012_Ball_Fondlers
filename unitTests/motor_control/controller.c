#include "motor_test.h"

static float en_rpmR = 0;
static float en_rpmL = 0;

static float dt = DT;

static float motor_R_integral = 0;
static float motor_R_prev_error = 0;

static float motor_L_integral = 0;
static float motor_L_prev_error = 0;

// Power to linear speed conversion
float speed_power(float power){
    if (power == 0) return 0;
    return (LINEAR_SPEED_FACTOR * log(power) + LINEAR_SPEED_OFFSET) * sgn(power);
}

// Power to rpm conversion
float power_rpm(float rpm){
    if (rpm == 0) return 0;
    return sgn(rpm) * pow(E, (((fabs(rpm)/RADIAN_T0_RPM) * WHEEL_DIAMETER/2 -LINEAR_SPEED_OFFSET)/LINEAR_SPEED_FACTOR));
}

void update_controller_readings(float rpmR, float rpmL, float dt){
    en_rpmR = rpmR;
    en_rpmL = rpmL;
    dt = dt;
}

// PID Controller for the right motor
float pid_R(float setpointR){
    float error = setpointR - en_rpmR;
    motor_R_integral = motor_R_integral + error * dt;
    float derivative = (error - motor_R_prev_error) / dt;
    float bias = power_rpm(setpointR);
    float output = MOTOR_R_KP * error + MOTOR_R_KI * motor_R_integral + MOTOR_R_KD * derivative + bias;
    motor_R_prev_error = error;
    return output;
}

// PID Controller for the left motor
float pid_L(float setpointL){
    float error = setpointL - en_rpmL;
    motor_L_integral = motor_L_integral + error * dt;
    float derivative = (error - motor_L_prev_error) / dt;
    float bias = power_rpm(setpointL);
    float output = MOTOR_L_KP * error + MOTOR_L_KI * motor_L_integral + MOTOR_L_KD * derivative + bias;
    motor_L_prev_error = error;
    return output;
}

// We can use an energy balance equation to get a rough estimate of the byte value of the motor power.