#ifndef ITF_TEMP_H
#define ITF_TEMP_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project Defines */
#include "projdefines.h"

typedef struct itf_temp_sensor itf_temp_sensor_t;

struct itf_temp_sensor {
    bool (*init)(itf_temp_sensor_t *this, TickType_t timeout);
    bool (*get_temp)(itf_temp_sensor_t *this, int16_t *temp, TickType_t timeout);
};

#endif // IFT_TEMP_H
