#include "../config.h"

// @Unizz20

/*
1. the ball is in collection point
2. ensure that the ball is collected
3. if ball escapes collection point, return to search_task
*/

int collect_task(){
    int success = 0;
    if (success == 1){
        return DELIVER_BALL;
    }
    else{
        return COLLECT_BALL;
    }
}