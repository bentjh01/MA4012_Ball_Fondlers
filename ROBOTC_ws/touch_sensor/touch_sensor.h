#ifndef TOUCH_H
#define TOUCH_H

#include "../config.h"
#include "../pinout.h"

void init_touch_sensor(void);
void read_touch_sensor(void);
void increment_counter(void);

#endif // TOUCH_H