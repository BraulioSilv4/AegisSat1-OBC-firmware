#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "msp430fr2433.h"

/** Sets the CE IO for communication with NRF24L01 to HIGH */
void CE_HIGH(void);
/** Sets the CE IO for communication with NRF24L01 to HIGH */
void CE_LOW(void);

/** Initializes MSP430FR2433 GPIO pins to their required functionalities. */
void init_GPIO(void);

#endif  // GPIO_DRIVER_H
