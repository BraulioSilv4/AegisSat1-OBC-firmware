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
#include "projdefines.h"

/* Communication */
void comms_task(void *pvParameters);

/* Info & Status Gathering */
void EPS_task(void *pvParameters);
void GPS_task(void *pvParameters);
void HK_task(void *pvParameters);
void IMU_task(void *pvParameters);
void payload_task(void *pvParameters);

/* Processing & Storage */
void ADCS_task(void *pvParameters);
void store_data_task(void *pvParameters);

/* System */
void watchdog_task(void *pvParameters);

/* Testing */
// void vGetGPS(void *pvParameters);
// void vGetTemperature(void *pvParameters);
// void vReadAHT20(void *pvParameters);

/* DEBUGGING */
// extern SemaphoreHandle_t xLedSemaphore;
// void vLedTurnOffTask(void *pvParameters);
// void vLedTurnOnTask(void *pvParameters);

void init_tasks();

#endif // TASKS_H
