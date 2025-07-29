#ifndef ADXL345_H
#define ADXL345_H

#include "I2C_component/I2C_component.h"

bool ADXL345_init(TickType_t timeout);
bool ADXL345_read(int16_t *x, int16_t *y, int16_t *z, TickType_t timeout);

#endif
