#include "AHT20_conversion_interface.h"

#if AHT20_CONVERSION_MODE == AHT20_IMPL_FASTINT

/*
 * This formula was created from the provided in the datasheet,
 * but avoids floating point operation which are not supported 
 * by hardware on the MSP430FR2433.
 * Max precision is 1 decimal case since multiplying any value
 * provided by the aht20 for temperature by >= 20000 could't
 * be stored in an int32_t. 
 * Output is in dec degree celsius.
 * T(C)=(R*2000/2^20) - 500
 */
int16_t aht20_compute_temperature(uint32_t raw_temp) {
    // 2 >> 20 => division by 2^20
    return (int16_t)(((raw_temp * 2000) >> 20) - 500);
}

/*
 * This formula was created from the one provided in the datasheet,
 * but avoids floating point operations.
 * Max precision is 1 decimal case since any value provided by the
 * aht20 for humidity multiplied by >= 10000 couldn't be stored in an int32.
 * Output is in dec percentage relative humidity.
 * RH[%]=((R * 1000) / 2^20)
 */
int16_t aht20_compute_humidity(uint32_t raw_hum) {
    return  (int16_t)((raw_hum * 1000) >> 20);
}

#endif
