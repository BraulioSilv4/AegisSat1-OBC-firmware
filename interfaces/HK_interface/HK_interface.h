#ifndef HK_INTERFACE_H
#define HK_INTERFACE_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project defines */
#include "projdefines.h"

/* Components Includes */
#include "components/AHT20_component/AHT20_component.h"

bool init_HK_peripherals(TickType_t timeout);
bool read_temperature(int16_t *temperature, TickType_t timeout);
bool read_humidity(int16_t *humidity, TickType_t timeout);
bool read_pressure(int32_t *pressure, TickType_t timeout);

#endif  // HK_INTERFACE_H
