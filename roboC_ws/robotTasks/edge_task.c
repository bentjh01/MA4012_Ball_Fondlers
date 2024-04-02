#include "../config.h"

// @FANZIFU

static float edge_linX = 0.0;
static float edge_angZ = 0.0;

int edge_detected(int FL, int BL, int BR, int FR){
	if (FL > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
	if (BL > LINE_BL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
	if (BR > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
	if (FR > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
}

void edge_avoid(....){
    
}

float get_edge_linX(){
	return edge_linX;
}

float get_edge_angZ(){
	return edge_angZ;
}