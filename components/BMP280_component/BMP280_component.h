#ifndef BMP280_COMPONENT_H
#define BPM280_COMPONENT_H

#include "I2C_component/I2C_component.h"

bool BMP280_init(TickType_t timeout);

bool BMP280_read_temp_press(uint32_t *raw_temp, uint32_t *raw_press, TickType_t timeout, uint8_t n_tries);

#endif  // BMP280_COMPONENT_H
