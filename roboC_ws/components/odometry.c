#include "../config.h"
#include "support.c"

/* _____________________________________________________________________________________________________________________

ROBOT STATE
_____________________________________________________________________________________________________________________ */


/**
 * @brief Updates the x-coordinate of the robot's odometry based on the given inputs.
 * @param x The current x-coordinate of the robot.
 * @param yaw The current yaw angle of the robot.
 * @param linX The linear velocity of the robot in the x-direction.
 * @param rpmL The RPM (Rotations Per Minute) of the left wheel.
 * @param rpmR The RPM (Rotations Per Minute) of the right wheel.
 * @param dt The time step for the update.
 * @return The updated x-coordinate of the robot's odometry.
 */
float update_odometry_x(float x, float yaw, float linX, float rpmL, float rpmR, float dt){
    // Predict the state of the robot
    float state_x = x + linX * dt * cosDegrees(yaw);

    // Predict the state of the robot using encoders
    float encoder_x = x + calculate_linear_x(rpmL, rpmR) * dt * cosDegrees(yaw);

    // Calculate the innovation
    float encoder_x_innovation = encoder_x - state_x;

    // Apply an alpha beta filter 
    return state_x + ENCODER_FILTER * encoder_x_innovation;
    // return state_x;
}

/**
 * @brief Updates the y-coordinate of the robot's odometry based on the given inputs.
 * @param y The current y-coordinate of the robot.
 * @param yaw The current yaw angle of the robot.
 * @param linX The linear velocity of the robot.
 * @param rpmL The RPM (Rotations Per Minute) of the left wheel.
 * @param rpmR The RPM (Rotations Per Minute) of the right wheel.
 * @param dt The time step for the update.
 * @return The updated y-coordinate of the robot's odometry.
 */
float update_odometry_y(float y, float yaw, float linX, float rpmL, float rpmR, float dt){
    // Predict the state of the robot
    float state_y = y + linX * dt * sinDegrees(yaw);

    // Predict the state of the robot using encoders
    float encoder_y = y + calculate_linear_x(rpmL, rpmR) * dt * sinDegrees(yaw);

    // Calculate the innovation
    float encoder_y_innovation = encoder_y - state_y;

    // Apply an alpha beta filter
    return state_y + ENCODER_FILTER * encoder_y_innovation;
    // return state_y;
}

/**
 * @brief Updates the yaw angle of the robot's odometry based on various sensor inputs.
 * @param yaw The current yaw angle of the robot.
 * @param angZ The angular velocity of the robot.
 * @param rpmL The left wheel's rotational speed in RPM (Revolutions Per Minute).
 * @param rpmR The right wheel's rotational speed in RPM (Revolutions Per Minute).
 * @param magneto_yaw The yaw angle measured by the magnetometer.
 * @param dt The time step for the update.
 * @return The updated yaw angle of the robot's odometry.
 */
float update_odometry_yaw(float yaw, float angZ, float rpmL, float rpmR, float magneto_yaw, float dt) {
    float output_yaw;
    // Predict the state of the robot
    float state_yaw = yaw + angZ * dt;

    // Predict the state of the robot using encoders
    float encoder_yaw = yaw + calculate_angular_z(rpmL, rpmR) * dt;

    float encoder_yaw_innovation = encoder_yaw - state_yaw;
    float magnetometer_yaw_innovation = magneto_yaw - discretise_yaw(state_yaw);
    if (abs(magnetometer_yaw_innovation) > 0.0){
        output_yaw = state_yaw + MAGNETO_FILTER * magnetometer_yaw_innovation;
    }
    else{
        output_yaw = state_yaw + ENCODER_FILTER * encoder_yaw_innovation;
    }
    // output_yaw = state_yaw + ENCODER_FILTER * encoder_yaw_innovation; // TESTING

    // output_yaw = state_yaw + (ENCODER_FILTER * encoder_yaw_innovation + MAGNETO_FILTER * magnetometer_yaw_innovation)/(ENCODER_FILTER + MAGNETO_FILTER);

    output_yaw = wrap_to_pi(output_yaw);

    return output_yaw;
}

/**
 * @brief Updates the odometry linear X position of the robot based on the given inputs.
 * @param cmd_linX The desired linear X position of the robot.
 * @param rpmL The RPM (Rotations Per Minute) of the left wheel.
 * @param rpmR The RPM (Rotations Per Minute) of the right wheel.
 * @param dt The time interval in seconds.
 * @return The updated odometry linear X position of the robot.
 */
float update_odometry_linX(float cmd_linX, float rpmL, float rpmR, float dt){
    // Predict the state of the robot using encoders
    
    float encoder_linX = calculate_linear_x(rpmL, rpmR);

    float encoder_linear_velocity_innovation = encoder_linX - cmd_linX;

    return cmd_linX + ENCODER_FILTER * encoder_linear_velocity_innovation;
}

/**
 * @brief Updates the odometry angular Z value based on various sensor inputs.
 * @param yaw The current yaw value of the robot.
 * @param cmd_angZ The desired angular Z value.
 * @param rpmL The left wheel's RPM (Rotations Per Minute).
 * @param rpmR The right wheel's RPM (Rotations Per Minute).
 * @param magneto_yaw The yaw value obtained from the magnetometer.
 * @param dt The time interval between updates.
 * @return The updated odometry angular Z value.
 */
float update_odometry_angZ(float cmd_angZ, float rpmL, float rpmR, float dt){
    // Predict the state of the robot using encoders
    float encoder_angZ = calculate_angular_Z(rpmL, rpmR);

    // Calculate the innovation
    float encoder_angular_velocity_innovation = encoder_angZ - cmd_angZ;

    // Apply a alpha beta filter
    return cmd_angZ + ENCODER_FILTER * encoder_angular_velocity_innovation;
}