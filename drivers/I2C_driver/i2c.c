#include "i2c.h"

I2C_Mode MasterMode = IDLE_MODE;

/* The Register Address/Command to use */
uint8_t TransmitRegAddr = 0;

static StaticSemaphore_t xI2CSemaphoreState;
static StaticSemaphore_t xI2CDoneSemaphoreState;
SemaphoreHandle_t xI2CSemaphore     = NULL; 
SemaphoreHandle_t xI2CDoneSemaphore = NULL;

/* ReceiveBuffer: Buffer used to receive data in the ISR
 * RXByteCtr: Number of bytes left to receive
 * ReceiveIndex: The index of the next byte to be received in ReceiveBuffer
 * TransmitBuffer: Buffer used to transmit data in the ISR
 * TXByteCtr: Number of bytes left to transfer
 * TransmitIndex: The index of the next byte to be transmitted in TransmitBuffer
 * */
uint8_t ReceiveBuffer[MAX_I2C_BUFFER_SIZE] = {0};
uint8_t RXByteCtr = 0;
uint8_t ReceiveIndex = 0;
uint8_t TransmitBuffer[MAX_I2C_BUFFER_SIZE] = {0};
uint8_t TXByteCtr = 0;
uint8_t TransmitIndex = 0;

//******************************************************************************
// I2C Functions ***************************************************************
//******************************************************************************
I2C_Mode I2C_Master_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t count) {
    /* Initialize state machine */
    MasterMode = TX_REG_ADDRESS_MODE;
    TransmitRegAddr = reg_addr;

    uint8_t copyIndex = 0;
    for (copyIndex = 0; copyIndex < count; copyIndex++)
    {
        TransmitBuffer[copyIndex] = reg_data[copyIndex];
    }

    TXByteCtr = count;
    RXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    /* Initialize slave address and interrupts */
    UCB0I2CSA = dev_addr;
    UCB0IFG &= ~(UCTXIFG + UCRXIFG);         // Clear any pending interrupts
    UCB0IE &= ~UCRXIE;                       // Disable RX interrupt
    UCB0IE |= UCTXIE;                        // Enable TX interrupt

    UCB0CTLW0 |= UCTR + UCTXSTT;             // I2C TX, start condition
    __bis_SR_register(GIE);                  // enable interrupts

    return MasterMode;
}

I2C_Mode I2C_Master_ReadReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t count) {
    /* Initialize state Mmachine */
    MasterMode = TX_REG_ADDRESS_MODE;   // State machine mode for transmiting
    TransmitRegAddr = reg_addr;         
    RXByteCtr = count;                  // Number of bytes to read from slave
    TXByteCtr = 0;
    ReceiveIndex = 0;
    TransmitIndex = 0;

    /* Initialize slave address and interrupts */
    UCB0I2CSA = dev_addr;
    UCB0IFG &= ~(UCTXIFG + UCRXIFG);    // Clear any pending interrupts
    UCB0IE &= ~UCRXIE;                  // Disable RX interrupt
    UCB0IE |= UCTXIE;                   // Enable TX interrupt

    UCB0CTLW0 |= UCTR + UCTXSTT;        // I2C TX, start condition
    __bis_SR_register(GIE);             // Enable Global Interrupts

    return MasterMode;
}

I2C_Mode I2C_Master_WriteSlave(uint8_t dev_addr, uint8_t *reg_data, uint8_t count) {
    MasterMode = TX_DATA_MODE;      // Set State Machine to start sending immediatly
    cpymem((void *)TransmitBuffer, (void *)reg_data, count);
    TXByteCtr = count;
    TransmitIndex = 0;

    UCB0I2CSA = dev_addr;
    UCB0IFG &= ~(UCTXIFG + UCRXIFG);         // Clear any pending interrupts
    UCB0IE &= ~UCRXIE;                       // Disable RX interrupt
    UCB0IE |= UCTXIE;                        // Enable TX interrupt

    UCB0CTLW0 |= UCTR + UCTXSTT;             // I2C TX, start condition
    __bis_SR_register(GIE);                  // enable interrupts

    return MasterMode;
}

//******************************************************************************
// Device Initialization *******************************************************
//******************************************************************************
void init_I2C() {
    // I2C pins
    P1SEL0 |= BIT2 | BIT3;
    P1SEL1 &= ~(BIT2 | BIT3);  // Setting Pin 1.2, 1.3 as Primary module function

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // Init I2C
    UCB0CTLW0 = UCSWRST;                                    // Enable SW reset
    UCB0CTLW0 |= UCMODE_3 | UCMST | UCSSEL__SMCLK | UCSYNC; // I2C master mode, SMCLK
    UCB0BRW = I2C_CLOCK_DIVISOR;                            // fSCL = SMCLK/80 = ~100kHz
    UCB0I2CSA = DUMMY_I2C_ADDR;                             // Slave Address
    UCB0CTLW0 &= ~UCSWRST;                                  // Clear SW reset, resume operation
    UCB0IE |= UCNACKIE;

    xI2CSemaphore     = xSemaphoreCreateBinaryStatic(&xI2CSemaphoreState); 
    xI2CDoneSemaphore = xSemaphoreCreateBinaryStatic(&xI2CDoneSemaphoreState);
    xSemaphoreGive(xI2CSemaphore);
}

//******************************************************************************
// I2C Interrupt ***************************************************************
//******************************************************************************
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void) {
    uint8_t rx_val = 0;
    switch(__even_in_range(UCB0IV, USCI_I2C_UCBIT9IFG)) {
        case USCI_NONE:          break;         // Vector 0: No interrupts
        case USCI_I2C_UCALIFG:   break;         // Vector 2: ALIFG
        case USCI_I2C_UCNACKIFG: break;         // Vector 4: NACKIFG
        case USCI_I2C_UCSTTIFG:  break;         // Vector 6: STTIFG
        case USCI_I2C_UCSTPIFG:  break;         // Vector 8: STPIFG
        case USCI_I2C_UCRXIFG3:  break;         // Vector 10: RXIFG3
        case USCI_I2C_UCTXIFG3:  break;         // Vector 12: TXIFG3
        case USCI_I2C_UCRXIFG2:  break;         // Vector 14: RXIFG2
        case USCI_I2C_UCTXIFG2:  break;         // Vector 16: TXIFG2
        case USCI_I2C_UCRXIFG1:  break;         // Vector 18: RXIFG1
        case USCI_I2C_UCTXIFG1:  break;         // Vector 20: TXIFG1
        case USCI_I2C_UCRXIFG0:                 // Vector 22: RXIFG0
            rx_val = UCB0RXBUF;
            if(RXByteCtr) {                     // Store the received byte in the buffer
                ReceiveBuffer[ReceiveIndex++] = rx_val;
                RXByteCtr--;
            }

            if(RXByteCtr == 1) {                // If next byte is last set up STOP conditon    
                UCB0CTLW0 |= UCTXSTP;
            } else if(RXByteCtr == 0) {         // If all bytes have been received
                UCB0IE &= ~UCRXIE;              // disable the receive interrupt
                MasterMode = IDLE_MODE;

                // Finished Receiving bytes completed
                BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                xSemaphoreGiveFromISR(xI2CDoneSemaphore, &xHigherPriorityTaskWoken);
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
            break;

        case USCI_I2C_UCTXIFG0:                 // Vector 24: TXIFG0
            switch(MasterMode) {
                case TX_REG_ADDRESS_MODE:
                    UCB0TXBUF = TransmitRegAddr;
                    if(RXByteCtr) {                         // If going to receive now
                        MasterMode = SWITCH_TO_RX_MODE;     // switch to receive mode state
                    } else {                                // If going to transfer more data
                        MasterMode = TX_DATA_MODE;          // switch to transfer mode state
                    }
                    break;

                case SWITCH_TO_RX_MODE:
                    UCB0IE |= UCRXIE;               // Enable RX interrupt
                    UCB0IE &= ~UCTXIE;              // Disable TX interrupt
                    UCB0CTLW0 &= ~UCTR;             // Switch to receiver I2C mode
                    MasterMode = RX_DATA_MODE;      // State to receive the data
                    UCB0CTLW0 |= UCTXSTT;           // Send repeated start

                    if(RXByteCtr == 1) {            // If only one byte to read
                        while((UCB0CTLW0 & UCTXSTT));
                        UCB0CTLW0 |= UCTXSTP;       // Send STOP condition
                    }
                    break;

                case TX_DATA_MODE:
                    if (TXByteCtr) {                // Send byte
                        UCB0TXBUF = TransmitBuffer[TransmitIndex++];
                        TXByteCtr--;
                    } else {                        // Done with transmission
                        UCB0CTLW0 |= UCTXSTP;       // Send stop condition
                        MasterMode = IDLE_MODE;
                        UCB0IE &= ~UCTXIE;          // disable TX interrupt

                        // Finished transmission
                        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                        xSemaphoreGiveFromISR(xI2CDoneSemaphore, &xHigherPriorityTaskWoken);
                        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
                    }
                    break;

                    default:
                        break;
                }     
                break;
            default: break;
    }
}


