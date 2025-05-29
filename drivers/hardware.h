#ifndef HARDWARE_H
#define HARDWARE_H

// MSP430 includes
#include <driverlib.h>
#include "cs.h"
#include "gpio.h"
#include "msp430fr2433.h"

// Helper includes
#include "ring_buffer.h"

// RTOS includes
#include "FreeRTOS.h"
#include "semphr.h"

#define MCLK_FREQ_MHZ 16                     // MCLK = 16MHz

extern RingBuffer uartRx;
extern SemaphoreHandle_t xUartSemaphore;

void init_clocks();
void init_UART();

#endif  // HARDWARE_H
