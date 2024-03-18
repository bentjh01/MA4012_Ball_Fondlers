#include "sensor_test.h"

// Params
#define dt 0.05
#define PI 3.14159265358979323846

#define CUTOFF_A 10 // [Hz]
#define ALPHA_A 1/(2*PI*CUTOFF_A*dt)

// support functions
float low_pass_filter(float input, float prev_input, float alpha){
    return alpha*input + (1-alpha)*prev_input;
}

// global variables
int line_FL_val;
int line_BL_val;
int line_BR_val;
int	line_FR_val;

int dis_L_val;
int dis_R_val;
int dis_mid_val;

int dis_top_val;

int enR;
int enL;

float current_time;

// sensors

void read_sensors(){
	line_FL_val = SensorValue[line_FL];
	line_BL_val = SensorValue[line_BL];
	line_BR_val = SensorValue[line_BR];
	line_FR_val = SensorValue[line_FR];

	dis_L_val = SensorValue[long_distance_L];
	dis_R_val = SensorValue[long_distance_R];
	dis_mid_val = SensorValue[short_distance];

	dis_top_val = SensorValue[long_distance_top];

	enR = getMotorEncoder[motor_R];
	enL = getMotorEncoder[motor_L];
}

void floppy(){
    float num = 5.0;
    float den = 13.0;
    float result = num/den;
}

task main()
{
	float dt = 0.05;
	while(1){
		clearTimer(T1);
        read_sensors();
		// Main Loop
        for (unsigned int i = 0; i < 1000; i++){
            floppy();
        }
        current_time = time1[T1]/1000;
		while (time1[T1] < 1/dt){}
	}
}
