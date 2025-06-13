#ifndef AHT20_COMPONENT_H
#define AHT20_COMPONENT_H

/* Drivers Includes */
#include "I2C_component/i2c_component.h"

/* AHT20 Conversions Include */
#include "AHT20_conversions/AHT20_conversion_interface.h"

/* Project Defines */
#include "projdefines.h"

/* Interfaces to Implement Includes */
#include "interfaces/Components_interfaces/itf_temp_sensor.h"
#include "interfaces/Components_interfaces/itf_humidity_sensor.h"


typedef struct AHT20_sensor {
    itf_temp_sensor_t temp_interface;
    itf_humidity_sensor_t hum_interface;
    int16_t temp;
    int16_t hum;
    bool new_temp;
    bool new_hum;
    bool initialized;
} AHT20_sensor_t;

void AHT20_sensor_create(AHT20_sensor_t *this);
bool AHT20_temp_init(itf_temp_sensor_t *this, TickType_t timeout);
bool AHT20_hum_init(itf_humidity_sensor_t *this, TickType_t timeout);
bool AHT20_read_temp(itf_temp_sensor_t *this, int16_t *out_temp, TickType_t timeout);
bool AHT20_read_humidity(itf_humidity_sensor_t *this, int16_t *out_hum, TickType_t timeout);

#endif  // AHT20_COMPONENT_H
