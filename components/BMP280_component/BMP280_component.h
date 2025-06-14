#ifndef BMP280_COMPONENT_H
#define BMP280_COMPONENT_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Drivers Includes */
#include "I2C_component/I2C_component.h"

/* Project Defines */
#include "projdefines.h"

/* Interfaces to Implement Includes */
#include "interfaces/Components_interfaces/itf_pressure_sensor.h"
#include "interfaces/Components_interfaces/itf_temp_sensor.h"

typedef struct BMP280_sensor {
    itf_pressure_sensor_t pressure_interface;
    itf_temperature_sensor_t temperature_interface;

    /* Implementation State */
    bool initialized;
    int16_t temperature;
    int32_t pressure;
    bool new_temperature;
    bool new_pressure;

    /* Trimming parameters */
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
} BMP280_sensor_t;

void BMP280_sensor_create(BMP280_sensor_t *this);

bool BMP280_init_temperature(itf_temperature_sensor_t *this, TickType_t timeout);
bool BMP280_init_pressure(itf_pressure_sensor_t *this, TickType_t timeout);
bool BMP280_read_pressure(itf_pressure_sensor_t *this, uint32_t *pressure, TickType_t timeout);
bool BMP280_read_temperature(itf_temperature_sensor_t *this, int16_t *temperature, TickType_t timeout);

#endif  // BMP280_COMPONENT_H
