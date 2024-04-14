#include "../config.h"
#include "components/components.h"

float collect_servo = 0.0;
float collect_linX = 0.0;
float collect_angZ = 0.0;

int collect_task(float servo_position, float distance_sensor_mid, float distance_sensor_top, int ball_in_chamber){
    static int collect_startup = TRIGGERED;
    static int collect_wait;

    if (collect_startup == TRIGGERED){
        collect_wait = COLLECT_WAIT;
        collect_startup = NOT_TRIGGERED;
    }

    if (servo_position == 0){
        //check if ball is ready to collect
        if(distance_sensor_mid <= READY_TO_COLLECT_THRESHOLD){
            collect_linX = MAX_SPEED;
            collect_angZ = 0.0;
            collect_servo = SERVO_COLLECT_POSITION;
        }
        else{
            collect_startup = TRIGGERED;
            return GOTO;
        }
    }
    else if (servo_position == SERVO_COLLECT_POSITION){
        collect_linX = 0.0;
        collect_angZ = 0.0;
        collect_servo = SERVO_COLLECT_POSITION;
        collect_wait --;
        if (collect_wait <= 0){
            // check if ball is caught
            if (ball_in_chamber == TRIGGERED){
                collect_startup = TRIGGERED;
                collect_linX = 0.0;
                collect_angZ = 0.0;
                return DELIVER;
            }
            else if (ball_in_chamber == NOT_TRIGGERED){
                collect_servo = 0.0; //open the gate
                collect_linX = MAX_SPEED;
                collect_angZ = 0.0;
                return GOTO;
            }
        }
    }
    return COLLECT;
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