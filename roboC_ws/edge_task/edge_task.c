#include "../config.h"

int edge_detected(int FL, int BL, int BR, int FR){
	if (line_FL_val > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
	if (line_BL_val > LINE_BL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
	if (line_BR_val > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
	if (line_FR_val > LINE_FL_THRESHOLD){
		return 1;
		} else {
		return 0;
	}
}

void edge_avoid(....){
    
}