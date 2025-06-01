#ifndef BMP280_INTERFACE_H
#define BPM280_INTERFACE_H

#include "I2C_interface/i2c_interface.h"

bool AHT20_init(TickType_t timeout);

bool AHT20_read_temp(int32_t *temp, int32_t *hum, TickType_t timeout);

#endif  // BPM280_INTERFACE_H
