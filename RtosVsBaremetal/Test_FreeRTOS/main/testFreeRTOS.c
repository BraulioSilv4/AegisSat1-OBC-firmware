/**
 * This code is a simple example of a FreeRTOS application that performs
 * a calculation N_TESTS times using FreeRTOS tasks and measures the time taken to complete each
 * calculation and the total time taken to complete all calculations.
 * It will be used to compare the performance of the same calculations using a baremetal application.
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
#include "freertos/semphr.h"
#include "../../config.c"

#define MICRO2MS(m) ((m)/1000)

SemaphoreHandle_t semaphore;

void work_task(void * pvParameters) {
    int64_t start = esp_timer_get_time();
    do_work();
    int64_t end = esp_timer_get_time();

    printf("Task %s calculation time: %lld ms\n",pcTaskGetName(NULL), MICRO2MS(end - start));
    
    xSemaphoreGive(semaphore);
        
    vTaskDelete(NULL);
}

void app_main(void) {
    semaphore = xSemaphoreCreateCounting(N_TESTS, 0);
    
    if (semaphore == NULL) {
        printf("Failed to create semaphore\n");
        return;
    }

    int64_t start = esp_timer_get_time();
  
    for (int i = 1; i <= N_TESTS; i++) {
        char task_name[100];
        sprintf(task_name, "work_task_%d", i);
        xTaskCreate(work_task, task_name, STACK_SIZE, NULL, PRIORITY, NULL);
    }

    for (int i = 0; i < N_TESTS; i++)
        xSemaphoreTake(semaphore, portMAX_DELAY);

    int64_t end = esp_timer_get_time();
    printf("Time taken to complete all calculations: %lld ms.\n", MICRO2MS(end - start));
}
