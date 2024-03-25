#ifndef CONFIG_H
#define CONFIG_H

#define DT 0.05

// DELIVER TASK
#define DELIVERY_YAW_TOLERANCE 5 // [degrees] Tolerance for the yaw angle to be considered as 0 for robot to move linearly
#define DELIVER_KP 1.0
#define DELIVER_KI 0.0
#define DELIVER_KD 0.0

// ROBOT PARAMETERS
#define MAX_SPEED 0.5 // [m/s] Maximum linear speed

#endif //CONFIG_#define LINE_FL_THRESHOLD 106
#define LINE_BL_THRESHOLD 344
#define LINE_BR_THRESHOLD 173
#define LINE_FR_THRESHOLD 138