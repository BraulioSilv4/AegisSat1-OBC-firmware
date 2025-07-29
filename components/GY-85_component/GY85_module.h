#ifndef BNO055_MODULE_H
#define BNO055_MODULE_H

#include "FreeRTOS.h"


/* Project Defines */
#include "projdefines.h"

#include "I2C_component/i2c_component.h"
#include "GY-85_component/ADXL345/ADXL345.h"
#include "GY-85_component/HMC5883L/HMC5883L.h"
#include "GY-85_component/ITG3200/ITG3200.h"

/* Interfaces to implement */
#include "interfaces/Components_interfaces/itf_imu_module.h"


typedef struct {
    itf_imu_module_t imu_interface;
} GY85_module_t;

void GY85_module_create(GY85_module_t * module); 

#endif
