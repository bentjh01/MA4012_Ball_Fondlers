#define FRONT_WALL 6
#define BACK_WALL  7
#define LEFTT_WALL 8
#define RIGHT_WALL 9


void wall_hit(){

	// NORTH
	if (yaw > -5 && yaw < 5){
		if (FL == 1 && FR == 1){
			return 6; // Front Wall 
		}
		else if {BL == 1 && BR == 1){
			return 7; // Back Wall 
		}
	}
	
	// NORTH EAST
	else if (yaw >= -85 && yaw < -5){
		if (FL == 1){
			return 6; // Front Wall
		}
		else if (FR == 1){
			return 9; // Right Wall
		}
		else if (BL == 1){
			return 8; // Left Wall
		}
		else if (BR == 1){
			return 7; // Back Wall
		}
	}
	
	// NORTH WEST
	else if (yaw < 85 && yaw >= 5){
		if (FL == 1){
			return 8; // Left Wall
		}
		else if (FR == 1){
			return 6; // Front Wall
		}
		else if (BL == 1){
			return 7; // Back Wall
		}
		else if (BR == 1){
			return 9; // Right Wall
		}
	}
	
	// EAST
	else if (yaw >= -95 && yaw < -85){
		if (FL == 1 && FR == 1){
			return 9; // Right Wall 
		}
		else if {BL == 1 && BR == 1){
			return 8; // LEft Wall 
		}
	}
	
	// SOUTH EAST
	else if (yaw >= -175 && yaw < -95){
		if (FL == 1){
			return 9; // Right Wall
		}
		else if (FR == 1){
			return 7; // Back Wall
		}
		else if (BL == 1){
			return 6; // Front Wall
		}
		else if (BR == 1){
			return 8; // Left Wall
		}
	}
	
	// SOUTH
	else if (yaw > 175 && yaw <= -175){
		if (FL == 1 && FR == 1){
			return 7; // Back Wall 
		}
		else if {BL == 1 && BR == 1){
			return 6; // Front Wall 
		}
	}

	// SOUTH WEST
	else if (yaw >= 95 && yaw < 175){
		if (FL == 1){
			return 7; // Back Wall
		}
		else if (FR == 1){
			return 8; // Left Wall
		}
		else if (BL == 1){
			return 9; // Right Wall
		}
		else if (BR == 1){
			return 6; // Front Wall
		}
	}
	
	// WEST
	else if (yaw >= 85 && yaw < 95){
		if (FL == 1 && FR == 1){
			return 8; // Left Wall 
		}
		else if {BL == 1 && BR == 1){
			return 9; // Right Wall 
		}
	}
	
	// NORTH WEST
	else if (yaw >= 5 && yaw < 85){
		if (FL == 1){
			return 8; // Left Wall
		}
		else if (FR == 1){
			return 6; // Front Wall
		}
		else if (BL == 1){
			return 7; // Back Wall
		}
		else if (BR == 1){
			return 9; // Right Wall
		}
	}
	
	else{ 
		return 0;
	}
		
}

