#include "../config.h"

static float collect_servo = 0.0;

int collect_task(float servo_position, float distance_sensor_mid, float distance_sensor_top, int ball_in_chamber){
    float collect_arm_position_err = SERVO_COLLECT_POSITION - servo_position;

    if (distance_sensor_mid < 0.05 && distance_sensor_top > 0.05){
        collect_servo = SERVO_COLLECT_POSITION;
    }

    if (fabs(collect_arm_position_err) < SERVO_TOLERANCE && ball_in_chamber == TRIGGERED){
        return DELIVER;
    }

    else if (ball_in_chamber == NOT_TRIGGERED){
        return SEARCH;
    }

    else {
        return COLLECT;
    }
}



float get_collect_servo(){
    return collect_servo;
}