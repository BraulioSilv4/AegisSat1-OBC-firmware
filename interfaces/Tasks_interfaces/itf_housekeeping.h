#ifndef ITF_HOUSEKEEPING_T
#define ITF_HOUSEKEEPING_T

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project defines */
#include "projdefines.h"

/* Interface Includes */
#include "Components_interfaces/itf_temp_sensor.h"
#include "Components_interfaces/itf_humidity_sensor.h"

typedef struct {
    itf_temp_sensor_t *temp_sensor;
    itf_humidity_sensor_t *humidity_sensor;
} HK_interface_t;

#endif  // ITF_HOUSEKEEPING_T
