#include "driverlib.h"

#include "I2C_driver/i2c.h"
#include "UART_driver/uart.h"
#include "CLOCK_driver/clocks.h"
#include "SPI_driver/spi.h"

#include "tasks.h"

SemaphoreHandle_t xLedSemaphore;

int main(void) {
    WDT_A_hold(WDT_A_BASE); // Stops watchdog
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    PMM_unlockLPM5();

    xLedSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xLedSemaphore);

    init_clocks();
    init_UART();
    init_I2C();
    init_SPI();

    init_tasks();

    vTaskStartScheduler();

    while(1);
}
