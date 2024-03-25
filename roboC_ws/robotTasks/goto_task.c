#include "../config.h"

// @ShaDowFrost2417

/*
1. approach the ball and keep it centered
2. if at any point, the ball turns out to be an opponent, return to search_task
3. if ball is in collection point, return to collect_task
*/

int goto_task(float x, float y, float yaw, float sensor_A, float sensor_B){
    int success = 0;
    int opponent_detected = 0;

    if (success == 1){
        return COLLECT_BALL;
    }
    else if (opponent_detected){
        return SEARCH_BALL;
    }
    else{
        return GOTO_BALL;
    }
}