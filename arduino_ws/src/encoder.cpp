#pragma config(Sensor, dgtl3,  right_encoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  left_encoder,   sensorQuadEncoder)


task encoder(){
	// Clear Encoders
	SensorValue[right_encoder] = 0;
	SensorValue[left_encoder] = 0;
	
	// Covert to Degrees/Radians (-647 to 647) -> 647ticks/rev
	int RE_deg_right = ((SensorValue[right_encoder])*(360/647));
	int RE_rad_right = (RE_deg_right * (pi/180));

	// Covert to Degrees/Radians (-647 to 647) -> 647ticks/rev
	int RE_deg_left = ((SensorValue[left_encoder])*(360/647));
	int RE_rad_left = (RE_deg_left * (pi/180));
	
}
