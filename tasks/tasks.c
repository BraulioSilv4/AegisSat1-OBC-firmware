#include "tasks.h"

void init_tasks() {
    /* Communication */
    static StackType_t commStack[200];
    static StaticTask_t commTCB;
    xTaskCreateStatic(comms_task, "Comm", 200,(void *) get_comm_interface(), 1, commStack, &commTCB);

    /* Info & Status Gathering */
    // xTaskCreate(EPS_task, "EPS", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    static StackType_t gpsStack[300];
    static StaticTask_t gpsTCB;
    xTaskCreateStatic(GPS_task, "GPS", 300, (void *)get_gps_interface(), 1, gpsStack, &gpsTCB);

    static StackType_t hkStack[200];
    static StaticTask_t hkTCB;
    xTaskCreateStatic(HK_task, "HK", 200, (void *)get_hk_interface(), 1, hkStack, &hkTCB);
    // xTaskCreate(IMU_task, "IMU", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    static StackType_t payloadStack[150];
    static StaticTask_t payloadTCB;
    xTaskCreateStatic(payload_task, "PL", 150, NULL, 1, payloadStack, &payloadTCB);

    /* Processing & Storage */
    // xTaskCreate(ADCS_task, "ADCS", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(store_data_task, "store", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    /* System */
    static StackType_t wdtStack[configMINIMAL_STACK_SIZE];
    static StaticTask_t wdtTCB;
    xTaskCreateStatic(watchdog_task, "wdt", configMINIMAL_STACK_SIZE, NULL, 2, wdtStack, &wdtTCB);

    /* DEBUGGING */
    // xTaskCreate(vLedTurnOnTask, "Turn on LED Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(vLedTurnOffTask, "Turn off LED Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}

void init_semaphores() {
    /* Info & Status Gathering */
    static StaticSemaphore_t hk_mutex_state;
    hk_buffer_mutex = xSemaphoreCreateBinaryStatic(&hk_mutex_state);
    xSemaphoreGive(hk_buffer_mutex);

    static StaticSemaphore_t gps_mutex_state;
    gps_buffer_mutex = xSemaphoreCreateBinaryStatic(&gps_mutex_state);
    xSemaphoreGive(gps_buffer_mutex);
}
