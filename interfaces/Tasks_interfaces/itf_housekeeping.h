#ifndef ITF_HOUSEKEEPING_T
#define ITF_HOUSEKEEPING_T

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project defines */
#include "projdefines.h"

/* Interface Includes */
#include "Components_interfaces/itf_humidity_sensor.h"
#include "Components_interfaces/itf_pressure_sensor.h"
#include "Components_interfaces/itf_temp_sensor.h"

typedef struct {
    itf_humidity_sensor_t *humidity_sensor;
    itf_pressure_sensor_t *pressure_sensor;
    itf_pressure_sensor_t *alternate;
    itf_temperature_sensor_t *temperature_sensor;
} HK_interface_t;

#endif  // ITF_HOUSEKEEPING_T
