#include <driverlib.h>
#include "cs.h"
#include "gpio.h"
#include "msp430fr2433.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "projdefs.h"
#include "task.h"

#include "freeRTOS_support.h"

void vLedToggleTask(void *pvParameters) {
    while (1) {
        GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);  // Toggle LED
        vTaskDelay(pdMS_TO_TICKS(500)); 
    }
}

int main(void) {
    initialize_clock();

    volatile unsigned long smclk_freq = CS_getACLK();

    WDT_A_hold(WDT_A_BASE);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    PMM_unlockLPM5();

    xTaskCreate(vLedToggleTask, "LED Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1); 
}
