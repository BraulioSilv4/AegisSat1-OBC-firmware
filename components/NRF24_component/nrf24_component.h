#ifndef NRF24L01_COMPONENT_H
#define NRF24L01_COMPONENT_H

#include "nrf24_lowlevel.h"
#include "nrf24_config.h"
#include <stdbool.h>

bool NRF24_data_available();
void NRF24_start_listening();
void NRF24_stop_listening();
bool NRF24_send_data(uint8_t * data, uint8_t length, TickType_t timeout);
bool NRF24_attempt_receive(uint8_t * buffer, uint8_t length);
void NRF24_Init();

#endif // NRF24L01_COMPONENT_H
