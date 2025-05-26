#include "hardware.h"
#include "tasks.h"

int main(void) {
    WDT_A_hold(WDT_A_BASE); // Stops watchdog
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    PMM_unlockLPM5();

    xLedSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xLedSemaphore);

    init_clocks();

    init_tasks();

    vTaskStartScheduler();

    while(1);
}
