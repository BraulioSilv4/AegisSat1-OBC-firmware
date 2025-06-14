#include "driverlib.h"

/* Driver Includes */
#include "I2C_driver/i2c.h"
#include "UART_driver/uart.h"
#include "CLOCK_driver/clocks.h"
#include "SPI_driver/spi.h"

/* Interfaces Implementations Instantiator */
#include "interfaces/instantiator.h"

/* Tasks Initialization */
#include "tasks.h"

/* For tests */
// #include "TIMER_driver/timer.h"

SemaphoreHandle_t xLedSemaphore;

int main(void) {
    WDT_A_hold(WDT_A_BASE); // Stops watchdog
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    PMM_unlockLPM5();

    init_clocks();
    init_UART();
    init_I2C();
    init_SPI();

    /* For Tests */
    // init_timer();

    instantiate_interfaces();

    init_semaphores();
    init_tasks();

    vTaskStartScheduler();

    while(1);
}
