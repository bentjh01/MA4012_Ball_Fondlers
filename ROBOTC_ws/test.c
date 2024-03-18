#pragma config(Sensor, in7,    line_FL,        sensorAnalog)
#pragma config(Sensor, in8,    line_BL,        sensorAnalog)
#pragma config(Sensor, in5,    line_BR,        sensorAnalog)
#pragma config(Sensor, in6,    line_FR,        sensorAnalog)
#pragma config(Sensor, in4,    long_distance_top, sensorAnalog)
#pragma config(Sensor, in3,    long_distance_L, sensorAnalog)
#pragma config(Sensor, in1,    long_distance_R, sensorAnalog)
#pragma config(Sensor, in2,    short_distance, sensorAnalog)
#pragma config(Sensor, dgtl4,  wheel_R_encoderA, sensorQuadEncoder)
#pragma config(Sensor, dgtl2,  wheel_L_encoderA, sensorQuadEncoder)
#pragma config(Motor,  port6,           wheel_R,       tmotorVex393_HBridge, PIDControl, encoderPort, dgtl4)
#pragma config(Motor,  port7,           wheel_L,       tmotorVex393_MC29, PIDControl, encoderPort, dgtl2)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)

#define line_FL in7
#define line_BL in8
#define line_BR in5
#define line_FR in6
#define long_distance_top in4
#define long_distance_L in3
#define long_distance_R in1
#define short_distance in2

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

// unsigned int c;

task main()
{
	while(1){
		//c = increment_count();

		line_FL_val = SensorValue[line_FL];
		line_BL_val = SensorValue[line_BL];
		line_BR_val = SensorValue[line_BR];
		line_FR_val = SensorValue[line_FR];

		dis_L_val = SensorValue[long_distance_L];
		dis_R_val = SensorValue[long_distance_R];
		dis_mid_val = SensorValue[short_distance];

		dis_top_val = SensorValue[long_distance_top];

		//motor[wheel_R] = -127;
		//motor[wheel_L] = -127;

		motor[servo] = 30;

		enR = getMotorEncoder(wheel_R);
    enL = getMotorEncoder(wheel_L);

		delay(1000);
		motor[wheel_R] = 0;
		motor[wheel_L] = 0;

	}
}
