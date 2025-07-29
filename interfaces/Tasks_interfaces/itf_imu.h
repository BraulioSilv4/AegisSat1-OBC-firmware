#ifndef ITF_IMU_TASK_H
#define ITF_IMU_TASK_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project defines */
#include "projdefines.h"

/* Component Includes */
#include "Components_interfaces/itf_imu_module.h"

typedef struct {
    itf_imu_module_t *imu_module;
} imu_interface_t;

#endif  // ITF_IMU_TASK_H
