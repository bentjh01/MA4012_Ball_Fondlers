#include "../config.h"

// @ShaDowFrost2417

/*
1. approach the ball and keep it centered
2. if at any point, the ball turns out to be an opponent, return to search_task
3. if ball is in collection point, return to collect_task
*/

#define FRONT   1
#define LEFT    2
#define RIGHT   3

int startup_phase = 1;
int ball_location;
int prev_ball_location;

int opponent_detected(float short_sensor_dist){
    // may need to move this to components into sensors.c
  if(short_sensor_dist <= OPP_CLOSENESS_THRESHOLD){
    //Theres an opp robot close in front
    return OPP_DETECTED;
  }
  else{
    return 0;
  }
}

int get_ball_location(float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float short_sensor_dist){
    // may need to move this to components into sensors.c
    // Returns 1 if a ball is detected, 0 otherwise
    // return 0 when opponent is detected
    if (left_sensor_dist <= BALL_THRESHOLD_LNR && left_sensor_dist <= right_sensor_dist){
        return LEFT;
    }
    else if(right_sensor_dist <= BALL_THRESHOLD_LNR && right_sensor_dist <= left_sensor_dist){
        return RIGHT;
    }
    else if(mid_sensor_dist <= BALL_THRESHOLD_MID && opponent_detected(short_sensor_dist) == 0){
        return FRONT;
    }
    else{
        return 0;
    }
}

int goto_task(float x, float y, float yaw, float left_sensor_dist, float right_sensor_dist, float mid_sensor_dist, float short_sensor_dist){
    if(get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, short_sensor_dist) != 0){
        ball_location = get_ball_location(left_sensor_dist, right_sensor_dist, mid_sensor_dist, short_sensor_dist);
    }

    //ROTATE UNTIL MIDDLE, MOVE FORWARD
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