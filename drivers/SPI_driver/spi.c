#include "spi.h"

#define SLAVE_CS_OUT P2OUT
#define SLAVE_CS_DIR P2DIR
#define SLAVE_CS_PIN BIT1

volatile uint8_t *txBuffer, *rxBuffer;
volatile uint16_t txLen = 0, rxLen = 0;
volatile uint16_t txIndex = 0, rxIndex = 0;

static SemaphoreHandle_t xSPISemaphore;

int spi_transfer(uint8_t *tx, uint8_t *rx, uint16_t len, uint32_t timeout) {
    txBuffer = tx;
    rxBuffer = rx;
    txLen = rxLen = len;
    txIndex = rxIndex = 0;

    volatile uint8_t dummy = UCA1RXBUF;  
    (void)dummy;

    SLAVE_CS_OUT &= ~SLAVE_CS_PIN; // Put CS low to begin transaction

    UCA1TXBUF = txBuffer[txIndex++]; // Initiate transaction by sending the first byte
    
    UCA1IE |= UCTXIE | UCRXIE;  // Enable TX and RX interrupts



    return xSemaphoreTake(xSPISemaphore, timeout);
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    switch (__even_in_range(UCA1IV, USCI_SPI_UCTXIFG)) {
        case USCI_SPI_UCRXIFG:
            if (rxIndex < rxLen)
                rxBuffer[rxIndex++] = UCA1RXBUF; // read byte from rx
            break;

        case USCI_SPI_UCTXIFG:
            if (txIndex < txLen)
                UCA1TXBUF = txBuffer[txIndex++]; // send next byte
            break;
    }

    if (rxIndex >= rxLen && txIndex >= txLen) {
        UCA1IE &= ~(UCRXIE | UCTXIE);  // Disable interrupts
        SLAVE_CS_OUT |= SLAVE_CS_PIN; // Deassert CS
        xSemaphoreGiveFromISR(xSPISemaphore, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void init_SPI() {
    P2SEL0 |= BIT4 | BIT5 | BIT6;   // P2.4 = SCLK, P2.5 = MISO, P2.6 = MOSI
    P2SEL1 &= ~(BIT4 | BIT5 | BIT6);

    SLAVE_CS_DIR |= SLAVE_CS_PIN; // P2.1 = CS
    SLAVE_CS_OUT |= SLAVE_CS_PIN;

    // Clock polarity select: inactive state is high, MSB first
    // 8-bit data, Synchronous, Master mode, 3-pin SPI, BRCLK source: SMCLK
    UCA1CTLW0 = UCSWRST; // **Put eUSCI module in reset**
    UCA1CTLW0 |= UCSYNC | UCMST | UCSSEL__SMCLK | UCMSB | UCCKPH;
    UCA1BRW = 80;          // BRCLK / UCBRx = UCxCLK
                            // 8MHz  / 80    = 100kHz

    
    UCA1CTLW0 &= ~UCSWRST; // **Initialize eUSCI module**
    

    xSPISemaphore = xSemaphoreCreateBinary();
}