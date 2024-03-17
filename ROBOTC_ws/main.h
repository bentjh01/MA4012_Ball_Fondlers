#ifndef MAIN_H
#define MAIN_H

#include "config.h"

#define SEARCH_TASK 1
#define GOTO_BALL_TASK 2
#define COLLECT_BALL_TASK 3
#define DELIVER_BALL_TASK 4

extern int task_state;

void init_main(void);
void run_main(void);

#endif // MAIN_H
