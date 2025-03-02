/**
 * This code is a simple example of a baremetal application that performs
 * a calculation N_TESTS times and measures the time taken to complete each
 * calculation and the total time taken to complete all calculations. 
 * It will be used to compare the performance of the same calculations using FreeRTOS tasks.
 */

#include <stdio.h>
#include "../../config.c"
#include <inttypes.h>
#include "sdkconfig.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_timer.h"

#define MICRO2MS(m) ((m)/1000)

void app_main(void) {
    int64_t start = esp_timer_get_time();
  
    for (int i = 0; i < N_TESTS; i++) {
        int64_t calc_start = esp_timer_get_time();
        do_work();
        int64_t calc_end = esp_timer_get_time();
        printf("Calculation %d time: %lld ms\n",i+1, MICRO2MS(calc_end - calc_start));
    }

    int64_t end = esp_timer_get_time();
    printf("Time taken to complete all calculations: %lld ms.\n", MICRO2MS(end - start));
}
