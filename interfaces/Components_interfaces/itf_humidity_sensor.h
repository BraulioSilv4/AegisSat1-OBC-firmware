#ifndef ITF_HUMIDITY_H
#define ITF_HUMIDITY_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project Defines */
#include "projdefines.h"

typedef struct itf_humidity_sensor itf_humidity_sensor_t;

struct itf_humidity_sensor {
    bool (*init)(itf_humidity_sensor_t *this, TickType_t timeout);
    bool (*get_hum)(itf_humidity_sensor_t *this, int16_t *hum, TickType_t timeout);
};

#endif // ITF_HUMIDITY_H
