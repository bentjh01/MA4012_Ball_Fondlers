#ifndef TOUCH_H
#define TOUCH_H

#include "../config.h"
#include "../pinout.h"

// int init_touch_sensor(void);
int read_touch_sensor(void);
unsigned int increment_counter(unsigned int counter);

#endif // TOUCH_H