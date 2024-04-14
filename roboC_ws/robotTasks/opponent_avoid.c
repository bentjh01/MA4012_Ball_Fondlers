#include "../config.h"

float opp_cmd_linX;
float opp_cmd_angZ;

int opponent_avoid_task(int prev_task, float left_sensor, float right_sensor){
    static int opponent_avoid_startup = 1;
    static int opponent_avoid_count = 0;

    opponent_avoid_count ++;

    if (opponent_avoid_startup == 1){
        opponent_avoid_count = 0;
        opponent_avoid_startup = 0;
    }
    opponent_avoid_count ++;
    opp_cmd_linX = -MAX_SPEED/2.0;
    if (detect_thing(left_sensor, OPP_DETECT_THRESHOLD)){
        opp_cmd_angZ = -MAX_TURN;
    }
    else{
        opp_cmd_angZ = MAX_TURN;
    }
    
    if (opponent_avoid_count >= OPP_AVOID_TIMER){
        opponent_avoid_startup = 1;
        return prev_task;
    }
    return AVOID_OPPONENT;
}

float get_opp_avoid_linX(){
    return opp_cmd_linX;
}

float get_opp_avoid_angZ(){
    return opp_cmd_angZ;
}