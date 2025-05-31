#ifndef UART_DRIVER_H
#define UART_DRIVER_H

// RTOS includes
#include "FreeRTOS.h"
#include "semphr.h"

#include "msp430fr2433.h"
#include "projdefines.h"

#include "ring_buffer.h"

extern RingBuffer uartRx;
extern SemaphoreHandle_t xUartByteReady;

void init_UART();

#endif  // UART_DRIVER_H
