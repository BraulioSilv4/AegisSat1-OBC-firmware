#include "BMP280_component.h"

/* Conversions Include */
#include "BMP280_conversions/BMP280_conversion_interface.h"

/***************************** Private Functions *****************************/

static bool BMP280_read(BMP280_sensor_t *this, TickType_t timeout) {
    if(!this->initialized) { return false; }

    // trigger read
    uint8_t ctrl_nmeas = (1 << 5) | (1 << 2) | 0x01; // forced mode; temperature sampling x1; pressure sampling x1;
    if(!I2C_write_slave(BMP280, BMP280_CTRL_MEAS_RW, &ctrl_nmeas, 1, timeout)) {
        return false;
    }

    // With current reading settings read takes 6.4 ms in wrost case 
    vTaskDelay(pdMS_TO_TICKS(10));

    uint8_t status;
    if(!I2C_read_slave(BMP280, BMP280_STATUS_R, 1, &status, 1, timeout)) {
        return false;
    }

    // Verify that reading has ended
    if(status & BMP280_MEASURING_BIT) {
        return false;
    }

    uint8_t buf[6] = {0};
    if(!I2C_read_slave(BMP280, BMP280_PRESS_MSB_R, 6, buf, sizeof(buf), timeout)) {
        return false;
    }

    uint32_t raw_pressure = 0; 
    uint32_t raw_temperature = 0;
    raw_pressure    = ((uint32_t)buf[0] << 12) | ((uint32_t)buf[1] << 4) | ((uint32_t)(buf[2] >> 4));
    raw_temperature = ((uint32_t)buf[3] << 12) | ((uint32_t)buf[4] << 4) | ((uint32_t)(buf[5] >> 4));

    // Compute temperature needs to be called first for t_fine to be computed
    if(this->implementation32) {
        this->temperature = (int16_t)bmp280_compute_temperature32(this, raw_temperature);
        this->pressure = bmp280_compute_pressure32(this, raw_pressure);
    } else {
        this->temperature = (int16_t)bmp280_compute_temperature_linear(this, raw_temperature);
        this->pressure = bmp280_compute_pressure_linear(this, raw_pressure);
    }
    this->new_temperature = true;
    this->new_pressure = true;
    
    return true;
}

static bool BMP280_init(BMP280_sensor_t *this, TickType_t timeout) {
    if(this->initialized) { return true; }

    uint8_t chip_id = 0;
    if(!I2C_read_slave(BMP280, BMP280_CHIP_ID_R, 1, &chip_id, 1, timeout)) {
        return false;
    }

    // Check if it is right chip
    if(chip_id != BMP280_CHIP_ID) {
        return false;
    }

    uint8_t config;  // Read the config first since bit 1 should not be altered
    if(!I2C_read_slave(BMP280, BMP280_CONFIG_RW, 1, &config, 1, timeout)) {
        return false;
    }

    config = (config & ~BMP280_CONFIG_MASK) | (0x00 & BMP280_CONFIG_MASK); // New configuration; t standby = 0; filter off; SPI off
    if(!I2C_write_slave(BMP280, BMP280_CONFIG_RW, &config, 1, timeout)) {
        return false;
    }

    this->initialized = true;
    return true;
}

/************************** End of Private Functions **************************/

/********************************* Public API *********************************/

bool BMP280_init_temperature(itf_temperature_sensor_t *this, TickType_t timeout) {
    BMP280_sensor_t *bmp280 = container_of(this, BMP280_sensor_t, temperature_interface);
    return BMP280_init(bmp280, timeout);
}
bool BMP280_init_pressure(itf_pressure_sensor_t *this, TickType_t timeout) {
    BMP280_sensor_t *bmp280 = container_of(this, BMP280_sensor_t, pressure_interface);
    return BMP280_init(bmp280, timeout);
}

bool BMP280_read_pressure(itf_pressure_sensor_t *this, uint32_t *pressure, TickType_t timeout) {
    BMP280_sensor_t *bmp280 = container_of(this, BMP280_sensor_t, pressure_interface);

    if(!bmp280->new_pressure) {
        if(!BMP280_read(bmp280, timeout)) return false;
    }

    *pressure = bmp280->pressure;
    bmp280->new_pressure = false;
    return true; 
}

bool BMP280_read_temperature(itf_temperature_sensor_t *this, int16_t *temperature, TickType_t timeout) {
    BMP280_sensor_t *bmp280 = container_of(this, BMP280_sensor_t, temperature_interface);

    if(!bmp280->new_temperature) {
        if(!BMP280_read(bmp280, timeout)) return false;
    }

    *temperature = bmp280->temperature;
    bmp280->new_temperature = false;
    return true;
}

/****************************** End of Public API ******************************/

void BMP280_sensor_create(BMP280_sensor_t *this) {
    this->pressure_interface.init = BMP280_init_pressure;
    this->pressure_interface.get_pressure = BMP280_read_pressure;
    this->temperature_interface.init = BMP280_init_temperature;
    this->temperature_interface.get_temperature = BMP280_read_temperature;

    /* Implementation State */
    this->initialized = false;
    this->new_pressure = false;
    this->new_temperature = false;
    this->pressure = 0;
    this->temperature = 0;

    /* Trimming values */
    this->dig_T1 = 0x6AEA;
    this->dig_T2 = 0x6488;
    this->dig_T3 = 0x0032;
    this->dig_P1 = 0x93B6;
    this->dig_P2 = 0xD732;
    this->dig_P3 = 0x0BD0;
    this->dig_P4 = 0x1FA6;
    this->dig_P5 = 0xFEE9;
    this->dig_P6 = 0xFFF9;
    this->dig_P7 = 0x3C8C;
    this->dig_P8 = 0xC6F8;
    this->dig_P9 = 0x1770;
}

void BMP280_sensor_create_32(BMP280_sensor_t *this) {
    this->pressure_interface.init = BMP280_init_pressure;
    this->pressure_interface.get_pressure = BMP280_read_pressure;
    this->temperature_interface.init = BMP280_init_temperature;
    this->temperature_interface.get_temperature = BMP280_read_temperature;

    /* Implementation State */
    this->initialized = false;
    this->new_pressure = false;
    this->new_temperature = false;
    this->pressure = 0;
    this->temperature = 0;
    this->implementation32 = true;

    /* Trimming values */
    this->dig_T1 = 0x6AEA;
    this->dig_T2 = 0x6488;
    this->dig_T3 = 0x0032;
    this->dig_P1 = 0x93B6;
    this->dig_P2 = 0xD732;
    this->dig_P3 = 0x0BD0;
    this->dig_P4 = 0x1FA6;
    this->dig_P5 = 0xFEE9;
    this->dig_P6 = 0xFFF9;
    this->dig_P7 = 0x3C8C;
    this->dig_P8 = 0xC6F8;
    this->dig_P9 = 0x1770;
}

void BMP280_sensor_create_linear(BMP280_sensor_t *this) {
    this->pressure_interface.init = BMP280_init_pressure;
    this->pressure_interface.get_pressure = BMP280_read_pressure;
    this->temperature_interface.init = BMP280_init_temperature;
    this->temperature_interface.get_temperature = BMP280_read_temperature;

    /* Implementation State */
    this->initialized = false;
    this->new_pressure = false;
    this->new_temperature = false;
    this->pressure = 0;
    this->temperature = 0;
    this->implementation32 = false;

    /* Trimming values */
    this->dig_T1 = 0x6AEA;
    this->dig_T2 = 0x6488;
    this->dig_T3 = 0x0032;
    this->dig_P1 = 0x93B6;
    this->dig_P2 = 0xD732;
    this->dig_P3 = 0x0BD0;
    this->dig_P4 = 0x1FA6;
    this->dig_P5 = 0xFEE9;
    this->dig_P6 = 0xFFF9;
    this->dig_P7 = 0x3C8C;
    this->dig_P8 = 0xC6F8;
    this->dig_P9 = 0x1770;
}

