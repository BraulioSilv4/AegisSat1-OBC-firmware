#include "ADXL345.h"

#define ADXL345_ADDR 0xA6

bool ADXL345_init(TickType_t timeout) {
    uint8_t data = 0x08;
    return I2C_write_slave(ADXL345_ADDR, 0x2D, &data, 1, timeout);
}

bool ADXL345_read(int16_t *x, int16_t *y, int16_t *z, TickType_t timeout) {
    uint8_t buf[6];
    if (!I2C_read_slave(ADXL345_ADDR, 0x32, 6, buf, sizeof(buf), timeout)) return false;
    *x = (int16_t)((buf[1] << 8) | buf[0]);
    *y = (int16_t)((buf[3] << 8) | buf[2]);
    *z = (int16_t)((buf[5] << 8) | buf[4]);
    return true;
}
