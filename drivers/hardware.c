#include "hardware.h"

/*
* This module is set up to comunicate with the GY_NEO6MV2 GPS that by default uses 9600 baud rate.
* The clockPrescalar, firstModReg, secondModReg and oversampling were pre-computed using the following 
* texas online tool - https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html.
* Parameters for the tool - EUSCI, 32.768KHz, 9600.
* The clock source is ACLK.
*/
void initialize_UART() {
    EUSCI_A_UART_initParam param = {
        EUSCI_A_UART_CLOCKSOURCE_ACLK,
        3,
        0,
        146,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION
    };

    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P1,
        GPIO_PIN5,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P1,
        GPIO_PIN4,
        GPIO_PRIMARY_MODULE_FUNCTION
    );

    volatile uint8_t status = EUSCI_A_UART_init(EUSCI_A0_BASE, &param);
    EUSCI_A_UART_enable(EUSCI_A0_BASE);
}

void initialize_clocks() {

}
