#include "HMC5883L.h"

#define HMC5883L_ADDR     0x1E

#define HMC5883L_REG_CONFIG_A   0x00
#define HMC5883L_REG_CONFIG_B   0x01
#define HMC5883L_REG_MODE       0x02
#define HMC5883L_REG_DATA_X_MSB 0x03

bool HMC5883L_init(TickType_t timeout) {
    uint8_t config_a = 0x70;  // 8-average, 15 Hz, normal measurement
    uint8_t config_b = 0xA0;  // Gain = 5
    uint8_t mode     = 0x00;  // Continuous measurement mode

    return I2C_write_slave(HMC5883L_ADDR, HMC5883L_REG_CONFIG_A, &config_a, 1, timeout) &&
           I2C_write_slave(HMC5883L_ADDR, HMC5883L_REG_CONFIG_B, &config_b, 1, timeout) &&
           I2C_write_slave(HMC5883L_ADDR, HMC5883L_REG_MODE, &mode, 1, timeout);
}

bool HMC5883L_read(int16_t *x, int16_t *y, int16_t *z, TickType_t timeout) {
    uint8_t buf[6];
    if (!I2C_read_slave(HMC5883L_ADDR, HMC5883L_REG_DATA_X_MSB, 6, buf, sizeof(buf), timeout)) return false;

    *x = (int16_t)((buf[0] << 8) | buf[1]);
    *z = (int16_t)((buf[2] << 8) | buf[3]);
    *y = (int16_t)((buf[4] << 8) | buf[5]);

    return true;
}
