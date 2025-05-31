#include "tasks.h"
#include "I2C_interface/i2c_interface.h"

void vGetTemperature(void *pvParameters) {
    uint8_t buffer[10];
    uint8_t I2C_read_fail = 0;

    while(1) {
        bool success = I2C_read_slave(
            BMP280, 
            BMP280_CHIP_ID_CMD, 
            1, 
            buffer, 
            10, 
            pdMS_TO_TICKS(1000)
        );

        if(success) {
            I2C_read_fail = 0;
            volatile uint8_t byte = buffer[0];
        } else {
            if(++I2C_read_fail >= I2C_MAX_ATTEMPTS) {
                reset_I2C();
                I2C_read_fail = 0;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
