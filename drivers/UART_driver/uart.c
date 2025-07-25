#include "uart.h"

/* Semaphore to notify available byte */
static StaticSemaphore_t xUartSemaphoreState;
SemaphoreHandle_t xUartByteReady;

RingBuffer uartRx = {.head = -1, .tail = -1};

//******************************************************************************
// Device Initialization *******************************************************
//******************************************************************************
void init_UART() {
    // Configure UART pins
    P1SEL0 |= BIT4 | BIT5;                    // set 2-UART pin as second function

    // Configure UART
    UCA0CTLW0 |= UCSWRST;
    UCA0CTLW0 |= UCSSEL__SMCLK;

    // Baud Rate calculation
    // 8000000/(16*9600) = 52.083
    // Fractional portion = 0.083
    // User's Guide Table 14-4: UCBRSx = 0x49
    // UCBRFx = int ( (52.083-52)*16) = 1
    UCA0BR0 = 52;                             // 8000000/16/9600
    UCA0BR1 = 0x00;
    UCA0MCTLW = 0x4900 | UCOS16 | UCBRF_1;

    UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI

    xUartByteReady = xSemaphoreCreateBinaryStatic(&xUartSemaphoreState);

    __bis_SR_register(GIE);         // Interrupts enabled
}

void enable_uart_interrupts() {
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
}

void disable_uart_interrupts() {
  UCA0IE &= ~UCRXIE;                        // Disable USCI_A0 RX interrupt
}

//******************************************************************************
// UART Interrupt ***************************************************************
//******************************************************************************
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG: {
        enqueue(&uartRx, UCA0RXBUF);
        xSemaphoreGiveFromISR(xUartByteReady, &xHigherPriorityTaskWoken);
    }
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
    default: break;
  }

  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
