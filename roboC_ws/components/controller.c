#include "../config.h"

/**
 * @brief Calculates the output of a PID controller for the right motor.
 * @param setpointR The desired setpoint for the right motor.
 * @param en_rpmR The current RPM (rotations per minute) of the right motor.
 * @param bias The bias value to be added to the output.
 * @param dt The time interval between each call to the function.
 * @return The output of the PID controller.
 */
float pid_R(float setpointR, float en_rpmR, float bias, float dt){
    static float motor_R_integral = 0;
    static float motor_R_prev_error = 0;
    float error = setpointR - en_rpmR;
    if (fabs(motor_R_integral) < INTEGRAL_LIMIT_R){
        motor_R_integral = motor_R_integral + error * dt;
    }
    float derivative = (error - motor_R_prev_error) / dt;
    float output = MOTOR_R_KP * error + MOTOR_R_KI * motor_R_integral + MOTOR_R_KD * derivative + bias;
    motor_R_prev_error = error;
    return output;
}

/**
 * @brief Calculates the output of the left motor PID controller.
 * @param setpointL The desired setpoint for the left motor.
 * @param en_rpmL The current RPM of the left motor.
 * @param bias The bias to be applied to the output.
 * @param dt The time interval between each call to the function.
 * @return The output of the PID controller.
 */
float pid_L(float setpointL, float en_rpmL, float bias, float dt){
    static float motor_L_integral = 0;
    static float motor_L_prev_error = 0;
    float error = setpointL - en_rpmL;
    if (fabs(motor_L_integral) < INTEGRAL_LIMIT_L){
        motor_L_integral = motor_L_integral + error * dt;
    }
    float derivative = (error - motor_L_prev_error) / dt;
    float output = MOTOR_L_KP * error + MOTOR_L_KI * motor_L_integral + MOTOR_L_KD * derivative + bias;
    motor_L_prev_error = error;
    return output;
}

// We can use an energy balance equation to get a rough estimate of the byte value of the motor power.