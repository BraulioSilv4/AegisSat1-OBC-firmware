#include "AHT20_component.h"

/* Conversions Include */
#include "AHT20_conversions/AHT20_conversion_interface.h"

static bool AHT20_read_raw(AHT20_sensor_t *this, TickType_t timeout) {
    uint8_t aht20_trig_arg[2] = {AHT20_TRIG_ARG_1, AHT20_TRIG_ARG_2};
    if(!I2C_write_slave(AHT20, AHT20_TIRG_MEASURE_CMD, aht20_trig_arg, 2, timeout)) return false;

    vTaskDelay(pdMS_TO_TICKS(100)); // Wait for 100ms for reading to be complete

    uint8_t status;
    if(!I2C_read_slave(AHT20, AHT20_STATUS_CMD, 1, &status, 1, timeout)) return false;
    if((status & AHT20_READ_STATUS)) return false;  // Could also wait more

    uint8_t buf[6];
    if(!I2C_read_slave(AHT20, AHT20, 6, buf, 6, timeout)) return false;

    uint32_t raw_temperature, raw_hum;
    raw_hum = ((uint32_t)buf[1] << 12)
                 | ((uint32_t)buf[2] << 4)
                 | ((uint32_t)(buf[3] >> 4) & 0x0F);

    
    raw_temperature = (((uint32_t)buf[3] & 0x0F) << 16)
                      | ((uint32_t)buf[4] << 8)
                      | ((uint32_t)buf[5]);

    this->temperature = aht20_compute_temperature(raw_temperature);
    this->hum = aht20_compute_humidity(raw_hum);
    this->new_temperature = true;
    this->new_hum = true;

    return true;
}

static bool AHT20_init(AHT20_sensor_t *this, TickType_t timeout) {
    if(this->initialized) { return true; }
    vTaskDelay(pdMS_TO_TICKS(40));  // Wait 40ms after power on
    
    uint8_t status;
    if(!I2C_read_slave(AHT20, AHT20_STATUS_CMD, 1, &status, 1, timeout)) return false;

    if(!(status & AHT20_CALIBRATION_EN)) {
        uint8_t aht20_init_arg[2] = {AHT20_INIT_ARG_1, AHT20_INIT_ARG_2};
        if(I2C_write_slave(AHT20, AHT20_INIT_CMD, aht20_init_arg, 2, timeout)) return false;
        vTaskDelay(pdMS_TO_TICKS(10)); // Wait 10ms
    }

    this->initialized = true;
    return true;
}

bool AHT20_temperature_init(itf_temperature_sensor_t *this, TickType_t timeout) {
    AHT20_sensor_t *aht20 = container_of(this, AHT20_sensor_t, temperature_interface);
    return AHT20_init(aht20, timeout);
}

bool AHT20_hum_init(itf_humidity_sensor_t *this, TickType_t timeout) {
    AHT20_sensor_t *aht20 = container_of(this, AHT20_sensor_t, hum_interface);
    return AHT20_init(aht20, timeout);
}


bool AHT20_read_temperature(itf_temperature_sensor_t *this, int16_t *out_temp, TickType_t timeout) {
    AHT20_sensor_t *aht20 = container_of(this, AHT20_sensor_t, temperature_interface);

    if(!aht20->new_temperature) {
        if(!AHT20_read_raw(aht20, timeout)) return false;
    }
    *out_temp = aht20->temperature;
    aht20->new_temperature = false;
    return true;
}

bool AHT20_read_humidity(itf_humidity_sensor_t *this, int16_t *out_hum, TickType_t timeout) {
    AHT20_sensor_t *aht20 = container_of(this, AHT20_sensor_t, hum_interface);

    if(!aht20->new_hum) {
        if(!AHT20_read_raw(aht20, timeout)) return false;
    }
    *out_hum = aht20->hum;
    aht20->new_hum = false;
    return true;
}

void AHT20_sensor_create(AHT20_sensor_t *this) {
    this->temperature_interface.init = AHT20_temperature_init;
    this->temperature_interface.get_temperature = AHT20_read_temperature;
    this->hum_interface.init = AHT20_hum_init;
    this->hum_interface.get_hum = AHT20_read_humidity;

    this->temperature = 0;
    this->hum = 0;
    this->new_temperature = false;
    this->new_hum = false;
    this->initialized = false;
}
