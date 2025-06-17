#include "gpio.h"

void CE_HIGH() {
    P1OUT |= BIT6;  // Set P1.6 high
}

void CE_LOW() {
    P1OUT &= ~BIT6; // Set P1.6 low
}

void init_GPIO() {
    P1DIR |= BIT6;  // Set P1.6 as output
    CE_LOW();       // Initialize CE pin to low
}
