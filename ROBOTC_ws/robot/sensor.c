// int line_sensor_FL;
// int line_sensor_BL;
// int line_sensor_BR;
// int line_sensor_FR;

// float long_distance_sensor_FL;
// float long_distance_sensor_FR;
// float long_distance_sensor_TP;
// float short_distance_sensor;

// int limit_switch_chamber;
// int limit_switch_BL;
// int limit_switch_BR;

// void read_compass(void);
// void read_line_sensors(void);
// void read_distance_sensors(void);
// void read_limit_switches(void);

// void read_all_sensors(){
//   read_line_sensors();
//   read_distance_sensors();
//   read_limit_switches();
//   read_compass();
// }

// void read_distance_sensors(void){
//   long_distance_sensor_FL = long_distance_convert(long_distance_sensor_FL_pin);
//   long_distance_sensor_FR = long_distance_convert(long_distance_sensor_FR_pin);
//   long_distance_sensor_TP = long_distance_convert(long_distance_sensor_TP_pin);
//   short_distance_sensor = short_distance_convert(short_distance_sensor_pin);
// }

// void read_limit_switches(void){
//   limit_switch_chamber = digitalRead(limit_switch_chamber_pin);
//   limit_switch_BL = digitalRead(limit_switch_BL_pin);
//   limit_switch_BR = digitalRead(limit_switch_BR_pin);
// }

void read_compass(void){
  int pin1 = SensorValue[touch_test];
  int pin2 = SensorValue[touch_test];
  int pin3 = SensorValue[touch_test];
  int pin4 = SensorValue[touch_test];

  int combination = pin1 << 3 + pin2 << 2 + pin3 << 1 + pin4;
  switch (combination)
  {
  case 0b1101:
    compass_bearing = NORTH;
    break;
  case 0b1001:
    compass_bearing = NORTH_EAST;
    break;
  case 0b1011:
    compass_bearing = EAST;
    break;
  case 0b0011:
    compass_bearing = SOUTH_EAST;
    break;
  case 0b0111:
    compass_bearing = SOUTH;
    break;
  case 0b0110:
    compass_bearing = SOUTH_WEST;
    break;
  case 0b1110:
    compass_bearing = WEST;
    break;
  case 0b1100:
    compass_bearing = NORTH_WEST;
    break;
  default:
    compass_bearing = NULL;
    break;
  }
}

void read_line_sensors(void){
  line_sensor_FL = analogRead(line_sensor_FL_pin);
  line_sensor_BL = analogRead(line_sensor_BL_pin);
  line_sensor_BR = analogRead(line_sensor_BR_pin);
  line_sensor_FR = analogRead(line_sensor_FR_pin);

  if (line_sensor_FL > LINE_SENSOR_THRESHOLD){
    line_sensor_FL = HIGH;
  }
  else{
    line_sensor_FL = LOW;
  }
  if (line_sensor_BL > LINE_SENSOR_THRESHOLD){
    line_sensor_BL = HIGH;
  }
  else{
    line_sensor_BL = LOW;
  }
  if (line_sensor_BR > LINE_SENSOR_THRESHOLD){
    line_sensor_BR = HIGH;
  }
  else{
    line_sensor_BR = LOW;
  }
  if (line_sensor_FR > LINE_SENSOR_THRESHOLD){
    line_sensor_FR = HIGH;
  }
  else{
    line_sensor_FR = LOW;
  }
  
}

float long_distance_convert(int sensor_value){
  float si_value = sensor_value * 5.0 / 1023.0;
  return si_value;
}
float short_distance_convert(int sensor_value){
  float si_value = sensor_value * 5.0 / 1023.0;
  return si_value;
}

