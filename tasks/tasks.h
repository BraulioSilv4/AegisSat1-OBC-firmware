#ifndef TASKS_H
#define TASKS_H

// REMOVE
#include "hardware.h"

// RTOS INCLUDES 
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

// MSP430 INCLUDES
#include "projdefs.h"

// INTERFACES INCLUDES 
#include "uart_interface.h"

extern SemaphoreHandle_t xLedSemaphore;
void vLedTurnOffTask(void *pvParameters);
void vLedTurnOnTask(void *pvParameters);
void vToggleLedOnUART(void *pvParameters);
void vGet_GPS(void *pvParameters);

void init_tasks();

#endif // TASKS_H
