#include "tasks.h"

#include "AHT20_interface/AHT20_interface.h"

void vReadAHT20(void *pvParameters) {
    int32_t temp;
    int32_t hum;
    uint8_t I2C_read_fail = 0;

    bool success = false;
    do {
        success = AHT20_init(pdMS_TO_TICKS(100));
        if(!success && ++I2C_read_fail >= I2C_MAX_ATTEMPTS) {
            reset_I2C();
            I2C_read_fail = 0;
        } else {
            break;
        } 
        vTaskDelay(pdMS_TO_TICKS(3000));
    } while(!success);

    success = false;
    I2C_read_fail = 0;

    while(1) {
        AHT20_read_temp(&temp, &hum, pdMS_TO_TICKS(100));

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
