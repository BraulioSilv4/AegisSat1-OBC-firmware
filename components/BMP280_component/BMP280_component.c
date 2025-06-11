#include "BMP280_component.h"

#define U16(msb, lsb) ((uint16_t)(((msb) << 8) | (lsb)))
#define S16(msb, lsb) ((int16_t)(((msb) << 8) | (lsb)))

bool BMP280_init(TickType_t timeout) {
    uint8_t chip_id = 0;
    if(!I2C_read_slave(BMP280, BMP280_CHIP_ID_R, 1, &chip_id, 1, timeout)) {
        return false;
    }

    // check if it is right chip
    if(chip_id != BMP280_CHIP_ID) {
        return false;
    }

    uint8_t config = 0x00;  // t_sb = 0.5ms, filter off
    if(!I2C_write_slave(BMP280, BMP280_CONFIG_RW, &config, 1, timeout)) {
        return false;
    }

    // uint8_t trim_bytes[BMP280_TRIM_BYTES];
    // if(!I2C_read_slave(
    //     BMP280, 
    //     BMP280_DIG_T1_LSB_R, 
    //     BMP280_TRIM_BYTES, 
    //     trim_bytes, 
    //     BMP280_TRIM_BYTES, 
    //     timeout)
    // ) {
    //     return false;
    // }

    // dig_T1 =    U16(trim_bytes[1], trim_bytes[0]);
    // dig_TX[0] = S16(trim_bytes[3], trim_bytes[2]);
    // dig_TX[1] = S16(trim_bytes[5], trim_bytes[4]);
    // dig_P1 =    U16(trim_bytes[7], trim_bytes[6]);
    // dig_PX[0] = S16(trim_bytes[9], trim_bytes[8]);
    // dig_PX[1] = S16(trim_bytes[11], trim_bytes[10]);
    // dig_PX[2] = S16(trim_bytes[13], trim_bytes[12]);
    // dig_PX[3] = S16(trim_bytes[15], trim_bytes[14]);
    // dig_PX[4] = S16(trim_bytes[17], trim_bytes[16]);
    // dig_PX[5] = S16(trim_bytes[19], trim_bytes[18]);
    // dig_PX[6] = S16(trim_bytes[21], trim_bytes[20]);
    // dig_PX[7] = S16(trim_bytes[23], trim_bytes[22]); 
    

    return true;
}

bool BMP280_read_temp_press(uint32_t *raw_temp, uint32_t *raw_press, TickType_t timeout, uint8_t n_tries) {
    // trigger read
    uint8_t ctrl_nmeas = (1 << 5) | (1 << 2) | 0x01; // forced mode
    if(!I2C_write_slave(BMP280, BMP280_CTRL_MEAS_RW, &ctrl_nmeas, 1, timeout)) {
        return false;
    }

    uint8_t tries = 0;
    uint8_t status = 0;
    do {
        I2C_read_slave(BMP280, BMP280_STATUS_R, 1, &status, 1, timeout);
        if(++tries == n_tries) return false;
    } while(status & BMP280_MEASURING_BIT);

    uint8_t buf[6];
    if(!I2C_read_slave(BMP280, BMP280_PRESS_MSB_R, 6, buf, sizeof(buf), timeout)) {
        return false;
    }

    *raw_press = ((uint32_t)buf[0] << 12) | ((uint32_t)buf[1] << 4) | ((uint32_t)(buf[2] >> 4));
    *raw_temp  = ((uint32_t)buf[3] << 12) | ((uint32_t)buf[4] << 4) | ((uint32_t)(buf[5] >> 4));
    return true;
}
