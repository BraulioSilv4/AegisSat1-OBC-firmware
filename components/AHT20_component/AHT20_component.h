#ifndef AHT20_COMPONENT_H
#define AHT20_COMPONENT_H

#include "I2C_component/i2c_component.h"
#include "AHT20_conversions/AHT20_conversion_interface.h"

bool AHT20_init(TickType_t timeout);

bool AHT20_read_temp(int16_t *out_temp, TickType_t timeout);

bool AHT20_read_humidity(int16_t *out_hum, TickType_t timeout);

#endif  // AHT20_COMPONENT_H
