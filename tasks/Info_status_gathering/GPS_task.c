#include "tasks.h"

/* Task Interface Includes */
#include "interfaces/Tasks_interfaces/itf_gps.h"

/* Packet Buffer Packet */
#include "Common/Packet_buffers/GPS/gps_packet_buffer.h"

/* Task Defines */
#define GPS_INIT_TIMEOUT_MS             1000
#define GPS_TASK_FREQUENCY_MS           1000
#define GPS_READ_TIMEOUT_MS             100000
#define WAIT_SEMPHR_MS                  10
#define GPS_TASK_FREQUENCY_TICKS        (pdMS_TO_TICKS(GPS_TASK_FREQUENCY_MS))

void GPS_task(void *pvParameter) {
    gps_interface_t *itf = (gps_interface_t *)pvParameter;
    itf_gps_module_t *gps = itf->gps_module;

    if(!gps->init(gps, pdMS_TO_TICKS(GPS_INIT_TIMEOUT_MS))) vTaskDelete(NULL);

    TickType_t xLastWakeTime = xTaskGetTickCount();
    bool read_success = false;
    while(1) {
        if(xSemaphoreTake(gps_buffer_mutex, pdMS_TO_TICKS(WAIT_SEMPHR_MS))) {
            read_success = gps->get_gps(
                gps, 
                &gps_packets[gps_next_packet_index].data, 
                pdMS_TO_TICKS(GPS_READ_TIMEOUT_MS)
            );

            gps_packets[gps_next_packet_index].valid = read_success;

            if((gps_available_packets + 1) <= GPS_PACKETS_NUM) gps_available_packets++;
            if(++gps_next_packet_index >= GPS_PACKETS_NUM) gps_next_packet_index = 0;
            xSemaphoreGive(gps_buffer_mutex);
        }
        vTaskDelayUntil(&xLastWakeTime, GPS_TASK_FREQUENCY_TICKS);
    }
}
