#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#include "I2C_driver/i2c.h"

#include "string_utils.h"

/*
 * This function waits without blocking other tasks for all data requested.
 * Data received is copied to buf. Buffer passed to the function is expected 
 * to have a size >= count. 
 * */
bool I2C_read_slave(uint8_t dev_addr, uint8_t reg_addr, uint8_t count, uint8_t * buf, uint8_t buf_size);

/*
 * This function writes reg_data to slave dev_addr register reg_addr.
 * */
bool I2C_write_slave(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t count);

#endif // I2C_INTERFACE_H
