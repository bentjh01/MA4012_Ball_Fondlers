#include "../config.h"



void wall_hit(int FL, int BL, int BR, int FR, float yaw){
    float discrete_yaw = discretise_yaw(yaw);
	// NORTH
	// if (yaw > -5 && yaw < 5){
	if (discrete_yaw == NORTH){
        if (FL == TRIGGERED && FR == TRIGGERED){
            return FRONT_WALL; // Front Wall 
        }
        else if (BL == 1 && BR == 1){
			return BACK_WALL; // Back Wall 
		}
    }
	// NORTH EAST
	// else if (yaw >= -85 && yaw < -5){
	else if (discrete_yaw == NORTH_EAST){
		if (FL == TRIGGERED){
			return FRONT_WALL; // Front Wall
		}
		else if (FR == TRIGGERED){
			return RIGHT_WALL; // Right Wall
		}
		else if (BL == TRIGGERED){
			return LEFT_WALL; // Left Wall
		}
		else if (BR == TRIGGERED){
			return BACK_WALL; // Back Wall
		}
	}
	
	// NORTH WEST
	// else if (yaw < 85 && yaw >= 5){
	else if (discrete_yaw == NORTH_WEST){
		if (FL == TRIGGERED){
			return LEFT_WALL; // Left Wall
		}
		else if (FR ==TRIGGERED){
			return FRONT_WALL; // Front Wall
		}
		else if (BL == TRIGGERED){
			return BACK_WALL; // Back Wall
		}
		else if (BR == TRIGGERED){
			return RIGHT_WALL; // Right Wall
		}
	}
	
	// EAST
	// else if (yaw >= -95 && yaw < -85){
	else if (discrete_yaw == EAST){
		if (FL == TRIGGERED && FR == TRIGGERED){
			return RIGHT_WALL; // Right Wall 
		}
		else if (BL == TRIGGERED && BR == TRIGGERED){
			return LEFT_WALL; // LEft Wall 
		}
	}
	
	// SOUTH EAST
	// else if (yaw >= -175 && yaw < -95){
	else if (SOUTH_EAST){
		if (FL == TRIGGERED){
			return RIGHT_WALL; // Right Wall
		}
		else if (FR == TRIGGERED){
			return BACK_WALL; // Back Wall
		}
		else if (BL == TRIGGERED){
			return FRONT_WALL; // Front Wall
		}
		else if (BR == TRIGGERED){
			return LEFT_WALL; // Left Wall
		}
	}
	
	// SOUTH
	// else if (yaw > 175 && yaw <= -175){
	else if (discrete_yaw == SOUTH){
		if (FL == TRIGGERED && FR == TRIGGERED){
			return BACK_WALL; // Back Wall 
		}
		else if (BL == TRIGGERED && BR == TRIGGERED){
			return FRONT_WALL; // Front Wall 
		}
	}

	// SOUTH WEST
	// else if (yaw >= 95 && yaw < 175){
	else if (discrete_yaw == SOUTH_WEST){
		if (FL == TRIGGERED){
			return BACK_WALL; // Back Wall
		}
		else if (FR == TRIGGERED){
			return LEFT_WALL; // Left Wall
		}
		else if (BL == TRIGGERED){
			return RIGHT_WALL; // Right Wall
		}
		else if (BR == TRIGGERED){
			return FRONT_WALL; // Front Wall
		}
	}
	
	// WEST
	// else if (yaw >= 85 && yaw < 95){
	else if (discrete_yaw == WEST){
		if (FL == TRIGGERED && FR == TRIGGERED){
			return LEFT_WALL; // Left Wall 
		}
		else if (BL == TRIGGERED && BR == TRIGGERED){
			return RIGHT_WALL; // Right Wall 
		}
	}
	
	// NORTH WEST
	// else if (yaw >= 5 && yaw < 85){
	else if (discrete_yaw == NORTH_WEST){
		if (FL == TRIGGERED){
			return LEFT_WALL; // Left Wall
		}
		else if (FR == TRIGGERED){
			return FRONT_WALL; // Front Wall
		}
		else if (BL == TRIGGERED){
			return BACK_WALL; // Back Wall
		}
		else if (BR == TRIGGERED){
			return RIGHT_WALL; // Right Wall
		}
	}
	
	else{ 
		return INVALID;
	}
		
}

