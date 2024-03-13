#pragma config(Sensor, dgtl3,  right_encoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  left_encoder,   sensorQuadEncoder)


task encoder(){
	// Clear Encoders
	SensorValue[right_encoder] = 0;
	SensorValue[left_encoder] = 0;
	
	// Covert to Degrees/Radians (-647 to 647) -> 647ticks/rev
	RE_deg = ((SensorValue[right_encoder])*(360/647));
	RE_rad = (RE_deg * (pi/180))
	
}
