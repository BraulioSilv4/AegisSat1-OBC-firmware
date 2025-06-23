#include "I2C_component.h"

bool I2C_write_slave(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t count, TickType_t timeout) {
    if(!xSemaphoreTake(xI2CSemaphore, timeout)) return false;

    I2C_Master_WriteReg(dev_addr, reg_addr, reg_data, count);

    bool success = xSemaphoreTake(xI2CDoneSemaphore, timeout);

    xSemaphoreGive(xI2CSemaphore);
    return success;
}


bool I2C_read_slave(uint8_t dev_addr, uint8_t reg_addr, uint8_t count, uint8_t * buf, uint8_t buf_size, TickType_t timeout) {
    if(!buf || buf_size < count) return false;

    if(!xSemaphoreTake(xI2CSemaphore, timeout)) return false; 

    I2C_Master_ReadReg(dev_addr, reg_addr, count);

    bool success = false;
    if(xSemaphoreTake(xI2CDoneSemaphore, timeout)) {
        uint8_t copyIndex = 0;
        for (copyIndex = 0; copyIndex < count; copyIndex++)
        {
            buf[copyIndex] = ReceiveBuffer[copyIndex];
        }
        success = true;
    } 

    xSemaphoreGive(xI2CSemaphore);
    return success;
}

bool I2C_write_to_slave(uint8_t dev_addr, uint8_t *reg_data, uint8_t count, TickType_t timeout) {
    if(!xSemaphoreTake(xI2CSemaphore, timeout)) return false;

    I2C_Master_WriteSlave(dev_addr, reg_data, count);

    bool success = xSemaphoreTake(xI2CDoneSemaphore, timeout);

    xSemaphoreGive(xI2CSemaphore);
    return success;
}
