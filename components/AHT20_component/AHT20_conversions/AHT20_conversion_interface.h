#ifndef AHT20_CONVERSION_INTERFACE_H
#define AHT20_CONVERSION_INTERFACE_H

#include "stdint.h"
#include "../AHT20_config.h"

#if AHT20_CONVERSION_RETURN_TYPE == AHT20_TYPE_FLOAT
float aht20_compute_temperature(uint32_t raw_temp);
float aht20_compute_humidity(uint32_t raw_hum);

#elif AHT20_CONVERSION_RETURN_TYPE == AHT20_TYPE_INT16
int16_t aht20_compute_temperature(uint32_t raw_temp);
int16_t aht20_compute_humidity(uint32_t raw_hum);

#endif

#endif // AHT20_CONVERSION_INTERFACE_H
