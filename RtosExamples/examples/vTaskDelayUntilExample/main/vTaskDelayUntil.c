/**
 * This example shows how vTaskDelayUntil works.
 * 
 * This function differs from vTaskDelay() in one important aspect: vTaskDelay()
 * specifies a time at which the task wishes to unblock relative to the time at 
 * which vTaskDelay() is called, whereas vTaskDelayUntil() specifies an absolute 
 * time at which the task wishes to unblock.
 * 
 * @ref https://www.freertos.org/Documentation/02-Kernel/04-API-references/02-Task-control/02-vTaskDelayUntil
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_timer.h"

#define MICRO2MS(m) (m/1000)
#define STACK_SIZE 2048
#define PRIORITY 1

void simulate_work(int work_time) { vTaskDelay(work_time/portTICK_PERIOD_MS); }

void task1(void * pvParams) {
    // xLastWakeTime indicates the last time the task was unblocked with vTaskDelayUntil
    TickType_t xLastWakeTime = 0;
    const TickType_t xFrequency = 100;

    int64_t start = 0;
    int64_t prev_task_start = 0;

    int work_time = 100;
    for(;;) {
        int64_t start_delay = esp_timer_get_time();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
        float delay_time = (float) MICRO2MS((esp_timer_get_time() - start_delay));

        int64_t start_exec = esp_timer_get_time();
        simulate_work(work_time);
        float exec_time = (float) MICRO2MS((esp_timer_get_time() - start_exec));

        float total_time = exec_time + delay_time;

        
        // printf("MS. vTaskDelayUntil(): %.f~%.f, Task work: %.f~%.f\n", 
        //     (float) start,
        //     start + delay_time,
        //     start + delay_time,
        //     start + total_time
        // );
        printf("Task work start: %.f. Time passed since last start: %.f\n", 
            (start + delay_time), 
            (start + delay_time - prev_task_start)
        );
        prev_task_start = start + delay_time;
        start += total_time;
    }
}

void app_main(void)
{
    xTaskCreate(
        task1,
        "CountTime",
        STACK_SIZE,
        NULL,
        PRIORITY,
        NULL
    );
}
 