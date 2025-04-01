#ifndef FREERTOS_SUPPORT_H
#define FREERTOS_SUPPORT_H

#include <driverlib.h>
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

void vApplicationSetupTimerInterrupt(void);
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);
void initialize_clock();

#endif // FREERTOS_SUPPORT_H

