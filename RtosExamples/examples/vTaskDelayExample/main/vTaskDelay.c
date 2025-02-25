/**
 * In this code we observe why vTaskDelay does not provide a good method 
 * of controlling the frequency of a periodic task. It is observable from 
 * the output that the task execution time and delay accumulate over
 * iterations causing a drift from the intended periodic schedule. 
 * 
 * This happens because vTaskDelay() suspends the task for the specified 
 * time relative to the moment it was called.  
 * 
 * @ref https://www.freertos.org/Documentation/02-Kernel/04-API-references/02-Task-control/01-vTaskDelay
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
    int64_t start = 0;
    int64_t prev_task_start = 0;

    int delay = 1000;
    int work_time = 10;
    for(;;) {
        int64_t start_delay = esp_timer_get_time();
        vTaskDelay(delay/portTICK_PERIOD_MS);
        float delay_time = (float) MICRO2MS((esp_timer_get_time() - start_delay));

        int64_t start_exec = esp_timer_get_time();
        simulate_work(work_time);
        float exec_time = (float) MICRO2MS((esp_timer_get_time() - start_exec));

        float total_time = exec_time + delay_time;

        // printf("MS. vTaskDelay(): %.f~%.f, Task work: %.f~%.f\n", 
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
