#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>
#include <Wire.h>

#include "../support/pid.h"
#include "../config.h"

constexpr int led_pin = 16;

extern PIDController* delivery_yaw_pid;

// TODO: Add pin numbers for all sensors

// IR Line Tracking Sensor
constexpr int line_sensor_FL_pin = 2;
constexpr int line_sensor_BL_pin = 3;
constexpr int line_sensor_BR_pin = 4;
constexpr int line_sensor_FR_pin = 5;

// Sharp Distance Sensor
constexpr int long_distance_sensor_FL_pin = A0;
constexpr int long_distance_sensor_FR_pin = A1;
constexpr int long_distance_sensor_TP_pin = A2;
constexpr int short_distance_sensor_pin = A3;

// Limit Switches
constexpr int limit_switch_chamber_pin = 6;
constexpr int limit_switch_BL_pin = 7;
constexpr int limit_switch_BR_pin = 8;

// Magnetometer
constexpr int magnetometer_pin1 = 9;
constexpr int magnetometer_pin2 = 10;
constexpr int magnetometer_pin3 = 11;
constexpr int magnetometer_pin4 = 12;

// I2C


void init_hardware(void);
void init_controllers(void);

#endif // HARDWARE_H
