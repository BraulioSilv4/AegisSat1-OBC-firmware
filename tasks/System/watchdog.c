#include "tasks.h"

/* Driver Include */
#include "WDT_driver/wdt.h"

#define WDT_INTERVAL_MS     500

void watchdog_task(void *pvParameter) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    WDT_start();
    while(1) {
        WDT_reset();
        WDT_dead();
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(WDT_INTERVAL_MS));
    }
}
