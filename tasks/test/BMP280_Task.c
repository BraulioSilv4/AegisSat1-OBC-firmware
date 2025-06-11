#include "tasks.h"
#include "BMP280_interface/BMP280_interface.h"

void vGetTemperature(void *pvParameters) {
    uint32_t raw_press = 0;
    uint32_t raw_temp = 0;
    uint8_t I2C_read_fail = 0;

    bool success = false;
    do {
        success = BMP280_init(pdMS_TO_TICKS(100));
        vTaskDelay(pdMS_TO_TICKS(3000));
        if(!success && ++I2C_read_fail >= I2C_MAX_ATTEMPTS) {
            reset_I2C();
            I2C_read_fail = 0;
        } 
    } while(!success);

    success = false;
    I2C_read_fail = 0;


    while(1) {
        success = BMP280_read_temp_press(&raw_temp, &raw_press, pdMS_TO_TICKS(100), BMP280_MAX_READ_TRIES);

        if(success) {
            I2C_read_fail = 0;
            // Do something
        } else {
            if(++I2C_read_fail >= I2C_MAX_ATTEMPTS) {
                reset_I2C();
                I2C_read_fail = 0;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
