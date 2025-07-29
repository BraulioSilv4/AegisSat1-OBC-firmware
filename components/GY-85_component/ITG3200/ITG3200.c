#include "ITG3200.h"

#define ITG3200_ADDR  0x68
#define ITG3200_PWR_MGMT  0x3E
#define ITG3200_DATA_REG  0x1D

bool ITG3200_init(TickType_t timeout) {
    uint8_t data = 0x00;
    return I2C_write_slave(ITG3200_ADDR, ITG3200_PWR_MGMT, &data, 1, timeout);
}

bool ITG3200_read(int16_t *x, int16_t *y, int16_t *z, TickType_t timeout) {
    uint8_t buf[6];
    if (!I2C_read_slave(ITG3200_ADDR, ITG3200_DATA_REG, 6, buf, sizeof(buf), timeout)) 
        return false;

    *x = (int16_t)((buf[0] << 8) | buf[1]);
    *y = (int16_t)((buf[2] << 8) | buf[3]);
    *z = (int16_t)((buf[4] << 8) | buf[5]);

    return true;
}
