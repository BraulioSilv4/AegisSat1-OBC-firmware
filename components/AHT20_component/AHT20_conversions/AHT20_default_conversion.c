#include "AHT20_conversion_interface.h"

#if AHT20_CONVERSION_MODE == AHT20_IMPL_DEFAULT

#define TWOPOW20 1048576.0f
/*
 * Conversion formula provided by AHT20 datasheet.
 * Output is in degree celsius.
 * T(C)=(R/2^20) * 200 - 50
 */
float aht20_compute_temperature(uint32_t raw_temp) {
    return ((float)raw_temp / TWOPOW20) * 200.f - 50.f;
}

/*
 * Conversion formula provided by AHT20 datasheet.
 * Output is in percentage relative humidity.
 * RH[%]=(R/2^20) * 100%
 */
float aht20_compute_humidity(uint32_t raw_hum) {
    return  ((float)raw_hum / TWOPOW20) * 100.f;
}

#endif
