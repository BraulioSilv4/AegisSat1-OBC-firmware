#include "tasks.h"

void init_tasks() {
    // xTaskCreate(vLedTurnOnTask, "Turn on LED Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(vLedTurnOffTask, "Turn off LED Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vGetGPS, "GG", 200, NULL, 1, NULL);
    xTaskCreate(vGetTemperature, "temp", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
}
