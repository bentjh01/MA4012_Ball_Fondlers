#include "../config.h"
#include "components/components.h"

static float collect_servo = 0.0;
static float collect_linX = 0.0;
static float collect_angZ = 0.0;

// int collect_task(float servo_position, float distance_sensor_mid, float distance_sensor_top, int opp_detected, int ball_in_chamber){
//     float collect_arm_position_err = SERVO_COLLECT_POSITION - servo_position;

//     //check if ball is ready to collect
//     if(distance_sensor_mid <= READY_TO_COLLECT_THRESHOLD){
//         collect_linX = 0.1;
//     	collect_angZ = 0.0;
//     	collect_servo = SERVO_COLLECT_POSITION;
//     }
//     else if(detect_ball(99.9 ,99.9 , distance_sensor_mid, distance_sensor_top, opp_detected) == 1 && distance_sensor_mid <= BALL_THRESHOLD_MID){
//     	collect_linX = 0.2;
//     	collect_angZ = 0.0;
//     	return COLLECT;
//     }
//     else{
//     	return SEARCH;
//     	//return COLLECT;
//     }

//     //check if ball is caught
//     if (fabs(collect_arm_position_err) < SERVO_TOLERANCE && ball_in_chamber == TRIGGERED){
//         collect_linX = 0.0;
//     	collect_angZ = 0.0;
//         return DELIVER;
//     }

//     else if (fabs(collect_arm_position_err) < SERVO_TOLERANCE && ball_in_chamber == NOT_TRIGGERED){
//         collect_servo = 0; //open the gate
//         collect_linX = 0.0;
//     	collect_angZ = 0.0;
//         return SEARCH;
//     		//return COLLECT;
//     }

//     else {
//         return COLLECT;
//     }
// }

int collect_task_alt(float mid_sensor, float arm_position){
    mid_sensor = min(mid_sensor, LIMIT_DISTANCE_READINGS);
    if (mid_sensor <= BALL_IN_CHAMBER_DISTANCE && arm_position == SERVO_COLLECT_POSITION){
        collect_linX = 0.0;
        collect_angZ = 0.0;
        collect_servo = 0.0;
        return DELIVER;
    }
    else if (mid_sensor <= READY_TO_COLLECT_THRESHOLD){
        collect_linX = MAX_SPEED;
        collect_angZ = 0.0;
        collect_servo = SERVO_COLLECT_POSITION;
        return COLLECT;
    }
    else{
        return SEARCH;
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


//int collect_task_alt()