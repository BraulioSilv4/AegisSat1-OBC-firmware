#ifndef HARDWARE_H
#define HARDWARE_H

#include <driverlib.h>
#include "cs.h"
#include "gpio.h"
#include "msp430fr2433.h"

void initialize_clocks();
void initialize_UART();

#endif  // HARDWARE_H
