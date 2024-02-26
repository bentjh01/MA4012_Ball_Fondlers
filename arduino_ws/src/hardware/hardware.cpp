#include "hardware.h"



void init_controllers(void){
	// PID Controllers
	PIDController* delivery_yaw_pid = new PIDController;
	pid_init(delivery_yaw_pid, 1.0, 0.0, 0.0, DELIVERY_AREA_DIRECTION);
}

void init_hardware(void){
	// blink led example
	pinMode(led_pin, OUTPUT);
	/*
	______________________________________________________________________________________________________________________

	SENSORS
	______________________________________________________________________________________________________________________
	*/

	// IR Line Tracking Sensor
	// FL = Front Left, BL = Back Right, etc.
	pinMode(line_sensor_FL_pin, INPUT);
	pinMode(line_sensor_BL_pin, INPUT);
	pinMode(line_sensor_BR_pin, INPUT);
	pinMode(line_sensor_FR_pin, INPUT);

	// Sharp Distance Sensor
	// TP = Top, etc.
	pinMode(long_distance_sensor_FL_pin, INPUT);
	pinMode(long_distance_sensor_FR_pin, INPUT);
	pinMode(long_distance_sensor_TP_pin, INPUT);
	pinMode(short_distance_sensor_pin, INPUT);

	// Limit Switches
	pinMode(limit_switch_chamber_pin, INPUT);
	pinMode(limit_switch_BL_pin, INPUT);
	pinMode(limit_switch_BR_pin, INPUT);

	// Magnetometer
	pinMode(magnetometer_pin1, INPUT);
	pinMode(magnetometer_pin2, INPUT);
	pinMode(magnetometer_pin3, INPUT);
	pinMode(magnetometer_pin4, INPUT);

	/*
	______________________________________________________________________________________________________________________
	
	COMMUNICATION
	______________________________________________________________________________________________________________________
	*/
	// I2C
	Wire.begin();

}
