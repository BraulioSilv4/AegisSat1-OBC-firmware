#ifndef ITF_GPS_TASK_H
#define ITF_GPS_TASK_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project defines */
#include "projdefines.h"

/* Component Includes */
#include "Components_interfaces/itf_gps_module.h"

typedef struct {
    itf_gps_module_t *gps_module;
} gps_interface_t;

#endif  // ITF_GPS_TASK_H
