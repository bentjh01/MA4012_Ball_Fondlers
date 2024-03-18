#ifndef PINOUT_H
#define PINOUT_H

#pragma config(Sensor, in1,    long_distance_R, sensorAnalog)
#pragma config(Sensor, in2,    short_distance, sensorAnalog)
#pragma config(Sensor, in3,    long_distance_L, sensorAnalog)
#pragma config(Sensor, in4,    long_distance_top, sensorAnalog)
#pragma config(Sensor, in5,    line_BR,        sensorAnalog)
#pragma config(Sensor, in6,    line_FR,        sensorAnalog)
#pragma config(Sensor, in7,    line_FL,        sensorAnalog)
#pragma config(Sensor, in8,    line_BL,        sensorAnalog)
#pragma config(Sensor, dgtl2,  wheel_L_encoderA, sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  wheel_R_encoderA, sensorQuadEncoder)
// #pragma config(Sensor, dgtl,  touch_BL,       sensorDigitalIn)
// #pragma config(Sensor, dgtl6,  touch_BR,       sensorDigitalIn)
// #pragma config(Sensor, dgtl7,  magnetometer_N, sensorDigitalIn)
// #pragma config(Sensor, dgtl8,  magnetometer_W, sensorDigitalIn)
// #pragma config(Sensor, dgtl9,  magnetometer_S, sensorDigitalIn)
// #pragma config(Sensor, dgtl10, magnetometer_E, sensorDigitalIn)
// #pragma config(Sensor, dgtl12, touch_test,     sensorDigitalIn)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           motor_R,       tmotorVex393_HBridge, PIDControl, encoderPort, dgtl2)
#pragma config(Motor,  port7,           motor_L,       tmotorVex393_MC29, PIDControl, encoderPort, dgtl4)

#define long_distance_R     in1
#define short_distance      in2
#define long_distance_L     in3
#define long_distance_top   in4
#define line_BR             in5
#define line_FR             in6
#define line_FL             in7
#define line_BL             in8
#define motor_R             port6
#define motor_L             port7
#define servo               port2

// #define touch_BL dgtl5
// #define touch_BR dgtl6
// #define magnetometer_N dgtl7
// #define magnetometer_W dgtl8
// #define magnetometer_S dgtl9
// #define magnetometer_E dgtl10
// #define touch_test dgtl12

#endif //PINOUT_H