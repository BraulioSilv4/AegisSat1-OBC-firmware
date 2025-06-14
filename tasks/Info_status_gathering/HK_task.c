#include "tasks.h"

/* Task Interface Include*/
#include "interfaces/Tasks_interfaces/itf_housekeeping.h"

/* Packet Include */
#include "tasks/Common/Packet_buffers/Housekeeping/housekeeping_packet_buffer.h"

/* Task Defines */
#define INIT_TIMEOUT_MS             1000
#define READ_TIMEOUT_MS             1000
#define WAIT_SEMPHR_MS              10
#define HK_TASK_FREQUENCY_MS        1000
#define HK_TASK_FREQUENCY_TICKS     (pdMS_TO_TICKS(HK_TASK_FREQUENCY_MS))

void HK_task(void *pvParameter) {
    HK_interface_t *itf = (HK_interface_t *)pvParameter;
    itf_humidity_sensor_t *humidity_sensor = itf->humidity_sensor;
    itf_pressure_sensor_t *pressure_sensor = itf->pressure_sensor;
    itf_temperature_sensor_t *temperature_sensor = itf->temperature_sensor;

    if(!humidity_sensor->init(humidity_sensor, pdMS_TO_TICKS(INIT_TIMEOUT_MS))) vTaskDelete(NULL);
    if(!pressure_sensor->init(pressure_sensor, pdMS_TO_TICKS(INIT_TIMEOUT_MS))) vTaskDelete(NULL);
    if(!temperature_sensor->init(temperature_sensor, pdMS_TO_TICKS(INIT_TIMEOUT_MS))) vTaskDelete(NULL);

    TickType_t xLastWakeTime = xTaskGetTickCount();
    while(1) {
        if (xSemaphoreTake(hk_buffer_mutex, pdMS_TO_TICKS(WAIT_SEMPHR_MS))) {
            if(!temperature_sensor->get_temperature(
                temperature_sensor, 
                &hk_packets[hk_next_packet_index].temperature, 
                pdMS_TO_TICKS(READ_TIMEOUT_MS)
            )) {
                hk_packets[hk_next_packet_index].temperature = INVALID_VALUE;
            }

            if(!humidity_sensor->get_hum(
                humidity_sensor, 
                &hk_packets[hk_next_packet_index].humidity, 
                pdMS_TO_TICKS(READ_TIMEOUT_MS)
            )) {
                hk_packets[hk_next_packet_index].humidity = INVALID_VALUE;
            }

            if(!pressure_sensor->get_pressure(
                pressure_sensor, 
                &hk_packets[hk_next_packet_index].pressure, 
                pdMS_TO_TICKS(READ_TIMEOUT_MS)
            )) {
                hk_packets[hk_next_packet_index].pressure = INVALID_VALUE;
            }

            // Future work get time and add to packet

            if(++hk_next_packet_index >= HK_PACKET_NUMBER) hk_next_packet_index = 0;
            xSemaphoreGive(hk_buffer_mutex);
        }
        vTaskDelayUntil(&xLastWakeTime, HK_TASK_FREQUENCY_TICKS);
    }
}
