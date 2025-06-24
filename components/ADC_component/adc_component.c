#include "adc_component.h"

bool read_ADC(uint16_t *result, TickType_t timeout) {
    if(!result) return false;

    if(!xSemaphoreTake(xADCSemaphore, timeout)) return false;

    trigger_ADC();      // Trigger a ADC reading
    if(!xSemaphoreTake(xADCDoneSemaphore, timeout)) {   // Wait for conversion complete signal
        xSemaphoreGive(xADCSemaphore);
        return false;
    }

    *result = ADC_Result;
    xSemaphoreGive(xADCSemaphore);
    return true;
}
