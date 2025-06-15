#include "BMP280_conversion_interface.h"

/*
 * Functions below are implemented as described
 * in the Bosch BMP280 datasheet section 8.2 
 * (Compensation formula in 32 bit fixed point).
 * BST-BMP280-DS001-11, Document revision 1.14
 */

//#if BMP280_CONVERSION_MODE == BMP280_IMPL_32BIT

static int32_t t_fine;

int32_t bmp280_compute_temperature32(BMP280_sensor_t *this, int32_t raw_temp) {
    int32_t var1;
    int32_t var2;
    int32_t T;
    var1 = ((((raw_temp>>3) - ((int32_t)this->dig_T1<<1))) * ((int32_t)this->dig_T2)) >> 11;
    var2 = (((((raw_temp>>4) - ((int32_t)this->dig_T1)) * ((raw_temp>>4) - ((int32_t)this->dig_T1))) >> 12) * ((int32_t)this->dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

uint32_t bmp280_compute_pressure32(BMP280_sensor_t *this, int32_t raw_pressure) {
    int32_t var1, var2;
    uint32_t p;
    var1 = (((int32_t)t_fine)>>1) - (int32_t)64000;
    var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t)this->dig_P6);
    var2 = var2 + ((var1*((int32_t)this->dig_P5))<<1);
    var2 = (var2>>2)+(((int32_t)this->dig_P4)<<16);
    var1 = (((this->dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t)this->dig_P2) * var1)>>1))>>18;
    var1 =((((32768+var1))*((int32_t)this->dig_P1))>>15);
    if (var1 == 0) {
        return 0; // avoid exception caused by division by zero
    }

    p = (((uint32_t)(((int32_t)1048576)-raw_pressure)-(var2>>12)))*3125;

    if (p < 0x80000000) {
        p = (p << 1) / ((uint32_t)var1);
    } else {
        p = (p / (uint32_t)var1) * 2;
    }

    var1 = (((int32_t)this->dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
    var2 = (((int32_t)(p>>2)) * ((int32_t)this->dig_P8))>>13;
    p = (uint32_t)((int32_t)p + ((var1 + var2 + this->dig_P7) >> 4));
    
    return p;
}

//#endif
