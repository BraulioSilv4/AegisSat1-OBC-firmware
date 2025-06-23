#include "PCF8575_component.h"

bool PCF8575_set_gpio(IO_expander_value_t set, TickType_t timeout) {
    return I2C_write_to_slave(PCF8575, (uint8_t *)&set, 2, timeout);
}

bool PCF8575_read_gpio(IO_expander_value_t *out, TickType_t timeout) {
    return I2C_read_slave(PCF8575, PCF8575, 2, (uint8_t *)out, 2, timeout);
}
