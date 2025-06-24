#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

/* Kernel Includes */
#include "FreeRTOS.h"
#include "semphr.h"

/* Project defines includes */
#include "projdefines.h"

/* Mutex to allow a task to use ADC */
extern SemaphoreHandle_t xADCSemaphore;

/* Binary semaphore to signal complete ADC conversion */
extern SemaphoreHandle_t xADCDoneSemaphore;

/* Variable to store ADC reading */
extern uint16_t ADC_Result;


void init_ADC();

void trigger_ADC();

#endif // ADC_DRIVER_H
