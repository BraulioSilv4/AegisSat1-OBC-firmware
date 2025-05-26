#ifndef HARDWARE_H
#define HARDWARE_H

#include <driverlib.h>
#include "cs.h"
#include "gpio.h"
#include "msp430fr2433.h"

#define MCLK_FREQ_MHZ 16                     // MCLK = 8MHz

void init_clocks();

void init_UART();

#endif  // HARDWARE_H
