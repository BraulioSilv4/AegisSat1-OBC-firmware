#include "tasks.h"

/* Task Interface Include*/
#include "interfaces/Tasks_interfaces/itf_housekeeping.h"

/* Task Defines */
#define INIT_TIMEOUT_MS   1000
#define READ_TIMEOUT_MS   1000

void HK_task(void *pvParameter) {
    HK_interface_t *itf = (HK_interface_t *)pvParameter;
    itf_humidity_sensor_t *humidity_sensor = itf->humidity_sensor;
    itf_temp_sensor_t *temp_sensor = itf->temp_sensor;

    if(!humidity_sensor->init(humidity_sensor, pdMS_TO_TICKS(INIT_TIMEOUT_MS))) vTaskDelete(NULL);
    if(!temp_sensor->init(temp_sensor, pdMS_TO_TICKS(INIT_TIMEOUT_MS))) vTaskDelete(NULL);

    int16_t temperature, humidity;

    while(1) {
        temp_sensor->get_temp(temp_sensor, &temperature, pdMS_TO_TICKS(READ_TIMEOUT_MS));
        humidity_sensor->get_hum(humidity_sensor, &humidity, pdMS_TO_TICKS(READ_TIMEOUT_MS));
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
