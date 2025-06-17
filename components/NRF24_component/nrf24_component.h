#ifndef NRF24L01_COMPONENT_H
#define NRF24L01_COMPONENT_H

#include "SPI_driver/spi.h"
#include "GPIO_driver/gpio.h"
#include "projdefines.h"
#include "string_utils.h"
#include <stdbool.h>

void NRF24_Init(void);
uint8_t NRF24_get_status(void);
void NRF24_start_listening(void);
bool NRF24_attempt_receive(uint8_t * buffer, uint8_t length);
bool NRF24_send_data(uint8_t * buffer, uint8_t length, TickType_t timeout);
bool NRF24_data_available(void);
uint8_t NRF24_read_register(uint8_t reg);

#endif // NRF24L01_COMPONENT_H
