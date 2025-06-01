#include "AHT20_interface.h"

bool AHT20_init(TickType_t timeout) {
    vTaskDelay(pdMS_TO_TICKS(40));  // Wait 40ms after power on
    
    uint8_t status;
    if(!I2C_read_slave(AHT20, AHT20_STATUS_CMD, 1, &status, 1, timeout)) return false;

    if(!(status & AHT20_CALIBRATION_EN)) {
        uint8_t aht20_init_arg[2] = {AHT20_INIT_ARG_1, AHT20_INIT_ARG_2};
        if(I2C_write_slave(AHT20, AHT20_INIT_CMD, aht20_init_arg, 2, timeout)) return false;
        vTaskDelay(pdMS_TO_TICKS(10)); // Wait 10ms
    }

    return true;
}

bool AHT20_read_temp(int32_t *temp, int32_t *hum, TickType_t timeout) {
    uint8_t aht20_trig_arg[2] = {AHT20_TRIG_ARG_1, AHT20_TRIG_ARG_2};
    if(!I2C_write_slave(AHT20, AHT20_TIRG_MEASURE_CMD, aht20_trig_arg, 2, timeout)) return false;

    vTaskDelay(pdMS_TO_TICKS(100)); // Wait for 100ms for reading to be complete

    uint8_t status;
    if(!I2C_read_slave(AHT20, AHT20_STATUS_CMD, 1, &status, 1, timeout)) return false;
    if((status & AHT20_READ_STATUS)) return false;  // Could also wait more

    uint8_t buf[6];
    if(!I2C_read_slave(AHT20, AHT20, 6, buf, 6, timeout)) return false;

    uint64_t raw;
    raw = (((uint32_t)buf[3] & 0x0F) << 16)
                      | ((uint32_t)buf[4] << 8)
                      | ((uint32_t)buf[5]);

    raw = raw * 20000;
    raw = (raw  >> 20) - 5000;
    *temp = (int32_t) raw;

    return true;
}
