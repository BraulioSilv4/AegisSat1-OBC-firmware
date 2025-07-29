#ifndef HMC5883L_H
#define HMC5883L_H

#include "I2C_component/I2C_component.h"

bool HMC5883L_init(TickType_t timeout);
bool HMC5883L_read(int16_t *x, int16_t *y, int16_t *z, TickType_t timeout);

#endif
