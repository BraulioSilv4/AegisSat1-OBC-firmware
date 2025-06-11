#include "HK_interface.h"

bool init_HK_peripherals(TickType_t timeout) {
    return AHT20_init(timeout);
}

bool read_temperature(int16_t *temperature, TickType_t timeout) {
    return AHT20_read_temp(temperature, timeout);
}

bool read_humidity(int16_t *humidity, TickType_t timeout) {
    return AHT20_read_humidity(humidity, timeout);
}

bool read_pressure(int32_t *pressure, TickType_t timeout) {
    return 0;
}
