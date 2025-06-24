#include "tasks.h"

#include "components/PCF8575_component/PCF8575_component.h"

#include "components/ADC_component/adc_component.h"

void payload_task(void *pvParameter) {
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    vTaskDelay(pdMS_TO_TICKS(5000));
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    IO_expander_value_t value = P00 | P11;
    volatile IO_expander_value_t reading = 0;
    uint16_t adc_reading = 0;

    while(1) {
        volatile bool res1 = PCF8575_set_gpio(value, pdMS_TO_TICKS(10));
        read_ADC(&adc_reading, pdMS_TO_TICKS(100));

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
