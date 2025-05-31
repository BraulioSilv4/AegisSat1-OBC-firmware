#include "I2C_interface.h"

bool I2C_write_slave(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t count) {
    if(count == 0) return false;        // Writing nothing?

    if(xSemaphoreTake(xI2CSemaphore, portMAX_DELAY)) {
        I2C_Master_WriteReg(dev_addr, reg_addr, reg_data, count);

        bool success = false;
        if(xSemaphoreTake(xI2CDoneSemaphore, portMAX_DELAY)) {
            success = true;
        }

        xSemaphoreGive(xI2CSemaphore);
        return success;

    }

    return false;
}


bool I2C_read_slave(uint8_t dev_addr, uint8_t reg_addr, uint8_t count, uint8_t * buf, uint8_t buf_size) {
    if(!buf || buf_size < count) return false;

    if(xSemaphoreTake(xI2CSemaphore, portMAX_DELAY)) {
        I2C_Master_ReadReg(dev_addr, reg_addr, count);

        bool success = false;
        if(xSemaphoreTake(xI2CDoneSemaphore, portMAX_DELAY)) {
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

    return false;
}
