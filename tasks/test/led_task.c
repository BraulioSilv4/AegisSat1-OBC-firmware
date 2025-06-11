#include "tasks.h"

void vLedTurnOffTask(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(xLedSemaphore, portMAX_DELAY) == pdTRUE) {
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0); // Turn LED OFF
            vTaskDelay(pdMS_TO_TICKS(500)); // Keep it off for 500 ms
            xSemaphoreGive(xLedSemaphore); // Give for the ON task
            vTaskDelay(pdMS_TO_TICKS(1)); 
        }
    }
}

void vLedTurnOnTask(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(xLedSemaphore, portMAX_DELAY) == pdTRUE) {
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0); // Turn LED ON
            vTaskDelay(pdMS_TO_TICKS(500)); // Keep it off for 500 ms
            xSemaphoreGive(xLedSemaphore); // Give for the OFF task
            vTaskDelay(pdMS_TO_TICKS(1)); 
        }
    }
}
