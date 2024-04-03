#include "../config.h"

// @Unizz20

/*
1. the ball is in collection point
2. ensure that the ball is collected
3. if ball escapes collection point, return to search_task
*/

static float collect_linX = 0.0;
static float collect_angZ = 0.0;
static float collect_servo = 0.0;

int collect_task(){
    int success = 0;
    if (success == 1){
        return DELIVER;
    }
    else{
        return COLLECT;
    }
}

float get_collect_linX(){
    return collect_linX;
}

float get_collect_angZ(){
    return collect_angZ;
}

float get_collect_servo(){
    return collect_servo;
}