#include "../config.h"

float wrap_to_pi(float angle){
    if (fabs(angle) > 180.0){
        if (angle < 0){
            return angle + 360.0;
        }
        else {
            return angle - 360.0;
        }
    }
    else{
        return angle;
    }
}

float read_compass(void){
  int combination = SensorValue[compass_south] << 3 + SensorValue[compass_east]  << 2 + SensorValue[compass_north]  << 1 + SensorValue[compass_west];
  switch (combination)
  {
  case 0b1101:
    return NORTH;
  case 0b1001:
    return NORTH_EAST;
  case 0b1011:
    return EAST;
  case 0b0011:
    return SOUTH_EAST;
  case 0b0111:
    return SOUTH;
  case 0b0110:
    return SOUTH_WEST;
  case 0b1110:
    return WEST;
  case 0b1100:
    return NORTH_WEST;
  default:
    return NULL;
  }
}

float discretise_yaw(float yaw){
    return round(yaw / 45) * 45;
}