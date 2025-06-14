#ifndef TIMER_TEST_H
#define TIMER_TEST_H

/* Project Includes */
#include "projdefines.h"

/*
 * This function setups the timer A1 for continuos mode.
 * Only use if testing.
 * The timer is configured so each tick is 1 us.
 * The maximum measurment it can do before overflow of the 
 * TA0R register is 65.535 ms
 */
void init_timer();

void start_counter();

uint16_t get_time_us();

#endif  // TIMER_TEST_H
