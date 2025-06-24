#ifndef ADC_COMPONENT_H
#define ADC_COMPONENT_H

/* Driver Includes */
#include "ADC_driver/adc.h"

/* Project Defines */
#include "projdefines.h"

bool read_ADC(uint16_t *result, TickType_t timeout);

#endif // ADC_COMPONENT_H
