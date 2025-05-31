#ifndef TASKS_H
#define TASKS_H

// RTOS INCLUDES 
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

// MSP430 INCLUDES
#include "msp430fr2433.h"
#include "gpio.h"
#include "projdefs.h"

// INTERFACES INCLUDES 
#include "UART_interface/uart_interface.h"

extern SemaphoreHandle_t xLedSemaphore;
void vLedTurnOffTask(void *pvParameters);
void vLedTurnOnTask(void *pvParameters);
void vToggleLedOnUART(void *pvParameters);
void vGetGPS(void *pvParameters);
void vGetTemperature(void *pvParameters);

void init_tasks();

#endif // TASKS_H
