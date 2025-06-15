#include "BMP280_conversion_interface.h"

/*
 * The functions below calculate pressure and temperature for the BMP280.
 * Temperature compensation formula was provided by the BMP280 datasheet.
 * (Compensation formula in 32 bit fixed point). BST-BMP280-DS001-11, Document revision 1.14
 * 
 * Pressure calculation is simplified as a linear regression (degree 1 polynomial) model
 * trained with data created by using the 32 bit formula provided in the datasheet
 *
 * To avoid floating point precision, the coefficients were scaled by 100.
 * To avoid using 64 bit variables this scaling factor should not be more than 1000.
 * Since t_fine at wrost will be represented by 21 bits (sum of two int32 variables)
 * and t_fine at wrost multiplied by 10000 would overflow a 32 bit variable.
 * Raw pressure readings are at max 20 bits (altough current configuration 
 * gives 16 bit resolution, see read function, 1x sampling = 16 bit resolution, see datasheet).
 *
 * By avoiding using floats and 64 bits variables this implementation decreases code
 * size and increases efficiency by not having to emulate floating point operations
 * and/or 64 bit operations.
 *
 * Pressure output example 10091652 = 100916.52 <=> 1009.16 hPa
 */
//#if BMP280_CONVERSION_MODE == BMP280_IMPL_LINEAR

static int32_t t_fine;

int32_t bmp280_compute_temperature_linear(BMP280_sensor_t *this, int32_t raw_temp) {
    int32_t var1;
    int32_t var2;
    int32_t T;
    var1 = ((((raw_temp>>3) - ((int32_t)this->dig_T1<<1))) * ((int32_t)this->dig_T2)) >> 11;
    var2 = (((((raw_temp>>4) - ((int32_t)this->dig_T1)) * ((raw_temp>>4) - ((int32_t)this->dig_T1))) >> 12) * ((int32_t)this->dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

// linear regression degree 1
// uint32_t _1pressure = (uint32_t)((-0.1633868f * raw_pressure) + (0.02374819f * t_fine) + 147718.7f);
uint32_t bmp280_compute_pressure_linear(BMP280_sensor_t *this, int32_t raw_pressure) {
    return (uint32_t)((-16 * raw_pressure) + (2 * t_fine) + 14771870);
}

//#endif
