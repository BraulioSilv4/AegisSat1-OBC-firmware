#include "AHT20_component.h"

static int16_t temp;
static int16_t hum;
static bool new_temp = false;
static bool new_hum = false;

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

static bool AHT20_read_raw(TickType_t timeout) {
    uint8_t aht20_trig_arg[2] = {AHT20_TRIG_ARG_1, AHT20_TRIG_ARG_2};
    if(!I2C_write_slave(AHT20, AHT20_TIRG_MEASURE_CMD, aht20_trig_arg, 2, timeout)) return false;

    vTaskDelay(pdMS_TO_TICKS(100)); // Wait for 100ms for reading to be complete

    uint8_t status;
    if(!I2C_read_slave(AHT20, AHT20_STATUS_CMD, 1, &status, 1, timeout)) return false;
    if((status & AHT20_READ_STATUS)) return false;  // Could also wait more

    uint8_t buf[6];
    if(!I2C_read_slave(AHT20, AHT20, 6, buf, 6, timeout)) return false;

    uint32_t raw_temp, raw_hum;
    raw_hum = ((uint32_t)buf[1] << 12)
                 | ((uint32_t)buf[2] << 4)
                 | ((uint32_t)(buf[3] >> 4) & 0x0F);

    
    raw_temp = (((uint32_t)buf[3] & 0x0F) << 16)
                      | ((uint32_t)buf[4] << 8)
                      | ((uint32_t)buf[5]);

    temp = aht20_compute_temperature(raw_temp);
    hum = aht20_compute_humidity(raw_hum);
    new_temp = true;
    new_hum = true;

    return true;
}

bool AHT20_read_temp(int16_t *out_temp, TickType_t timeout) {
    if(!new_temp) {
        if(!AHT20_read_raw(timeout)) return false;
    }
    *out_temp = temp;
    new_temp = false;
    return true;
}

bool AHT20_read_humidity(int16_t *out_hum, TickType_t timeout) {
    if(!new_hum) {
        if(!AHT20_read_raw(timeout)) return false;
    }
    *out_hum = hum;
    new_hum = false;
    return true;
}
