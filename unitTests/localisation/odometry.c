#include "localisation_config.h"
#include "support.c"

static float local_x;
static float local_y;
static float local_yaw;
static float local_linX;
static float local_angZ;

static float local_cmd_linX;
static float local_cmd_angZ;

static float local_rpmL;
static float local_rpmR;

static float local_magneto_yaw;

static float state_x;
static float state_y;
static float state_yaw;
static float state_linX;
static float state_angZ;

static float encoder_x;
static float encoder_y;
static float encoder_yaw;
static float encoder_linX;
static float encoder_angZ;

static float magneto_yaw;

/* _____________________________________________________________________________________________________________________

ROBOT STATE
_____________________________________________________________________________________________________________________ */

void update_odometry(float x, float y, float yaw, float linX, float angZ, float cmd_linX, float cmd_angZ, float rpmL, float rpmR, float magnetometer_yaw){
    local_x = x;
    local_y = y;
    local_yaw = yaw;
    local_linX = linX;
    local_angZ = angZ;
    local_cmd_linX = cmd_linX;
    local_cmd_angZ = cmd_angZ;

    local_rpmL = rpmL;
    local_rpmR = rpmR;

    local_magneto_yaw = magnetometer_yaw;

    ab_filter_update();
}

/**
 * @brief      Calculate pose of the robot using the state model
 * @return     predicted pose.value
 */
void predict_state(float x, float y, float yaw, float linX, float angZ, float cmd_linX, float cmd_angZ, float dt){
    state_x = x + linX * cos(yaw) * dt;
    state_y = y + linX * sin(yaw) * dt;
    state_yaw = yaw + angZ * dt;
    state_linX = cmd_linX;
    state_angZ = cmd_angZ;

    return;
}

/**
 * @brief      Calculate pose of the robot using the encoders
 * @return     predicted pose.value
 */
void predict_state_encoders(float x, float y, float yaw, float rpmL, float rpmR, float dt){
	float d_radL = rpmL / RADIAN_T0_RPM;
    float d_radR = rpmR / RADIAN_T0_RPM;

    encoder_x = x + (d_radR + d_radL) * WHEEL_DIAMETER / 4 * cos(yaw) * dt;
    encoder_y = y + (d_radR + d_radL) * WHEEL_DIAMETER / 4 * sin(yaw) * dt;
    encoder_yaw = yaw + (d_radR - d_radL) * WHEEL_DIAMETER / ROBOT_TRACK * dt;
    encoder_linX = (d_radL + d_radR) * WHEEL_DIAMETER/4;
    encoder_angZ = (d_radR - d_radL) * WHEEL_DIAMETER / ROBOT_TRACK;

    return;
}


/**
 * @brief      Calculate pose of the robot using the magetometer
 * @return     predicted pose.value
 */

float predict_state_magnetometer_yaw(float yaw){
    magneto_yaw = yaw;
    return;
}

/**
 * @brief      Alpha Beta Filter
 * @return     predicted pose.value
 */
void ab_filter_update(void){
    predict_state(local_x, local_y, local_yaw, local_linX, local_angZ, local_cmd_linX, local_cmd_angZ, DT);
    predict_state_encoders(local_x, local_y, local_yaw, local_rpmL, local_rpmR, DT);
    predict_state_magnetometer_yaw(local_magneto_yaw);
    
    float encoder_x_innovation = encoder_x - state_x;
    local_x = state_x + ENCODER_FILTER_GAIN * encoder_x_innovation;

    float encoder_y_innovation = encoder_y - state_y;
    local_y = state_y + ENCODER_FILTER_GAIN * encoder_y_innovation;

    float encoder_yaw_innovation = encoder_yaw - state_yaw;
    float magnetometer_yaw_innovation = magneto_yaw - discretise_yaw(state_yaw);
    local_yaw = state_yaw + ENCODER_FILTER_GAIN * encoder_yaw_innovation + MAGNETO_FILTER_GAIN * magnetometer_yaw_innovation;
    local_yaw = wrap_to_pi(local_yaw);

    float encoder_linear_velocity_innovation = encoder_linX - state_linX;
    local_linX = state_linX + ENCODER_FILTER_GAIN * encoder_linear_velocity_innovation;

    float encoder_angular_velocity_innovation = encoder_angZ - state_angZ;
    local_angZ = state_angZ + ENCODER_FILTER_GAIN * encoder_angular_velocity_innovation;
}

float get_robot_x(void){
    return local_x;
}

float get_robot_y(void){
    return local_y;
}

float get_robot_yaw(void){
    return local_yaw;
}

float get_robot_linX(void){
    return local_linX;
}

float get_robot_angZ(void){
    return local_angZ;
}