#ifndef ITF_PRESSURE_H
#define ITF_PRESSURE_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project Defines */
#include "projdefines.h"

typedef struct itf_pressure_sensor itf_pressure_sensor_t;

struct itf_pressure_sensor {
    bool (*init)(itf_pressure_sensor_t *this, TickType_t timeout);
    bool (*get_pressure)(itf_pressure_sensor_t *this, uint32_t *pressure, TickType_t timeout);
};

#endif // ITF_PRESSURE_H
