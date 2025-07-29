#ifndef TASKS_H
#define TASKS_H

/* Kernel Includes */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"

/* Project Defines */
#include "msp430fr2433.h"
#include "gpio.h"
#include "projdefs.h"
#include "projdefines.h"

/* Interfaces Provider */
#include "interfaces/instantiator.h"

/* Task Packet Buffers Includes */
#include "Common/Packet_buffers/Housekeeping/housekeeping_packet_buffer.h"
#include "Common/Packet_buffers/GPS/gps_packet_buffer.h"

/* Communication */
void comms_task(void *pvParameters);

/* Info & Status Gathering */
void EPS_task(void *pvParameters);
void GPS_task(void *pvParameters);
void HK_task(void *pvParameters);
void IMU_task(void *pvParams);
void payload_task(void *pvParameters);

/* Processing & Storage */
void ADCS_task(void *pvParameters);
void store_data_task(void *pvParameters);

/* System */
void watchdog_task(void *pvParameters);

/* DEBUGGING */
// extern SemaphoreHandle_t xLedSemaphore;
// void vLedTurnOffTask(void *pvParameters);
// void vLedTurnOnTask(void *pvParameters);

void init_tasks();
void init_semaphores();

#endif // TASKS_H
