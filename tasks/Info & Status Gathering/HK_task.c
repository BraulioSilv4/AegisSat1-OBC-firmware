#include "tasks.h"

#include "interfaces/HK_interface/HK_interface.h"

void HK_task(void *pvParameter) {
    if(!init_HK_peripherals(pdMS_TO_TICKS(100))) vTaskDelete(NULL);

    int16_t temperature, humidity;

    while(1) {
        read_humidity(&humidity, pdMS_TO_TICKS(100));
        read_temperature(&temperature, pdMS_TO_TICKS(100));
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
