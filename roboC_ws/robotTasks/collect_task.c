#include "../config.h"

static float collect_servo = 0.0;
static float collect_linX = 0.0;
static float collect_angZ = 0.0;

int collect_task(float servo_position, float distance_sensor_mid, int opp_detected){
    float collect_arm_position_err = SERVO_COLLECT_POSITION - servo_position;

    //check if ball is ready to collect
    if(distance_sensor_mid <= READY_TO_COLLECT_THRESHOLD && !opp_detected){
        collect_linX = 0.2;
    	collect_angZ = 0.0;
    	collect_servo = SERVO_COLLECT_POSITION;
    }
    else if(distance_sensor_mid <= BALL_THRESHOLD_MID && !opp_detected){
    	collect_linX = 0.2;
    	collect_angZ = 0.0;
    	return COLLECT;
    }
    else{
    	return SEARCH;
    }

    //check if ball is caught
    if (fabs(collect_arm_position_err) < SERVO_TOLERANCE && distance_sensor_mid <= 0){
        collect_linX = 0.0;
    	collect_angZ = 0.0;
        return DELIVER;
    }

    else if (fabs(collect_arm_position_err) < SERVO_TOLERANCE && distance_sensor_mid > 0){
        collect_servo = 0; //open the gate
        collect_linX = 0.0;
    	collect_angZ = 0.0;
        return SEARCH;
    }

    else {
        return COLLECT;
    }
}



float get_collect_servo(){
    return collect_servo;
}

/// @brief Function to get the linear for the search task
/// @return linear velocity in m/s
float get_collect_linX(){
    return collect_linX;
}

/// @brief Function to get the angular velocity for the search task
/// @return angular velocity in deg/s
float get_collect_angZ(){
    return collect_angZ;
}


int collect_task_alt()