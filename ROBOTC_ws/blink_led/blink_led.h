#ifndef BLINK_LED_H // prevents duplicate definition of the same library
#define BLINK_LED_H

#include "../pinout.h"
#include "../config.h"

void init_led(void);
void blink_led(unsigned int duration);

#endif // BLINK_LED_H
