#ifndef ITG3200_H
#define ITG3200_H

#include "I2C_component/I2C_component.h"

bool ITG3200_init(TickType_t timeout);
bool ITG3200_read(int16_t *x, int16_t *y, int16_t *z, TickType_t timeout);

#endif
