#include "tasks.h"
#include "I2C_interface/i2c_interface.h"

void vGetTemperature(void *pvParameters) {
    uint8_t buffer[10];

    while(1) {
        bool sc = I2C_read_slave(0x77, 0xD0, 1, buffer, 10);
        volatile uint8_t byte = buffer[0];
        if(byte == 0x58) {
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
        }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
        GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
