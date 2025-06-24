#include "adc.h"

SemaphoreHandle_t xADCSemaphore     = NULL;
SemaphoreHandle_t xADCDoneSemaphore = NULL;

uint16_t ADC_Result = 0;

void init_ADC() {
    static StaticSemaphore_t xADCSemaphoreState;
    static StaticSemaphore_t xADCDoneSemaphoreState;

    xADCSemaphore           = xSemaphoreCreateMutexStatic(&xADCSemaphoreState);
    xADCDoneSemaphore       = xSemaphoreCreateBinaryStatic(&xADCDoneSemaphoreState);
    xSemaphoreGive(xADCSemaphore);

    SYSCFG2 |= ADCPCTL7;                // configure P1.7 as ADC pin

    ADCCTL0 |= ADCSHT_6 | ADCON;        // sample and hold 128 cycles, ADC on
    ADCCTL1 |= ADCSHP;                  // ADCCLK = MODOSC; sampling timer; ADC conversion start source is ADCSC bit
    ADCCTL2 |= ADCRES;                  // 10-bit conversion results
    ADCIE   |= ADCIE0;                  // conversion complete interrupt enable
    ADCMCTL0 |= ADCINCH_7 | ADCSREF_1;  // A7 ADC input select; Vref is internal 1.5V

    PMMCTL0_H = PMMPW_H;                // Unlock the PMM registers
    PMMCTL2 |= INTREFEN;                // Enable internal reference 1.5V 
    __delay_cycles(400);                // Delay for reference settling
    __bis_SR_register(GIE);             // Enable global interrupts
}

void trigger_ADC() {
    ADCCTL0 |= ADCENC | ADCSC;
} 

#pragma vector = ADC_VECTOR
__interrupt void ADC_ISR(void) {
    ADC_Result = ADCMEM0;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xADCDoneSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
