#include "tasks.h"

void init_tasks() {
    /* Communication */
    // xTaskCreate(comms_task, "Comm", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    /* Info & Status Gathering */
    // xTaskCreate(EPS_task, "EPS", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(GPS_task, "GPS", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(HK_task, "HK", 200, (void *)get_hk_interface(), 1, NULL);
    // xTaskCreate(IMU_task, "IMU", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(payload_task, "pl", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    /* Processing & Storage */
    // xTaskCreate(ADCS_task, "ADCS", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(store_data_task, "store", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    /* System */
    // xTaskCreate(watchdog_task, "wdt", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    /* DEBUGGING */
    // xTaskCreate(vLedTurnOnTask, "Turn on LED Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(vLedTurnOffTask, "Turn off LED Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}

void init_semaphores() {
    /* Info & Status Gathering */
    hk_buffer_mutex = xSemaphoreCreateBinary();
    xSemaphoreGive(hk_buffer_mutex);
}
