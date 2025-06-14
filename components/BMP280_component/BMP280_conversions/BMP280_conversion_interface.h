#ifndef BMP280_CONVERSION_INTERFACE_H
#define BMP280_CONVERSION_INTERFACE_H

/* BMP280 Implementation Include */
#include "../BMP280_component.h"

/* Config Include */
#include "../BMP280_config.h"

#if BMP280_CONVERSION_MODE == BMP280_IMPL_32BIT
int32_t bmp280_compute_temperature(BMP280_sensor_t *this, int32_t raw_temp);
uint32_t bmp280_compute_pressure(BMP280_sensor_t *this, int32_t raw_pressure);

#elif BMP280_CONVERSION_MODE == BMP280_IMPL_64BIT
int64_t bmp280_compute_temperature(BMP280_sensor_t *this, int64_t raw_temp);
uint64_t bmp280_compute_pressure(BMP280_sensor_t *this, int64_t raw_pressure);

#endif

#endif // BMP280_CONVERSION_INTERFACE_H
