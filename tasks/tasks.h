#ifndef TASKS_H
#define TASKS_H

#include "hardware.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

#include "projdefs.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xLedSemaphore;
void vLedTurnOffTask(void *pvParameters);
void vLedTurnOnTask(void *pvParameters);

void init_tasks();

#endif // TASKS_H
