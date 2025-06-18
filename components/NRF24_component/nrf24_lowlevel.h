#ifndef NRF24L01_LOWLEVEL_H
#define NRF24L01_LOWLEVEL_H

#include "SPI_driver/spi.h"
#include "GPIO_driver/gpio.h"
#include "projdefines.h"
#include "string_utils.h"
#include "nrf24_config.h"
#include <stdbool.h>

uint8_t NRF24_read_register(uint8_t reg);
void  NRF24_write_register(uint8_t reg, uint8_t data);
void NRF24_write_payload(uint8_t * data, uint8_t length); 
void NRF24_read_payload(uint8_t * buffer, uint8_t length);
void NRF24_clear_flags();
uint8_t NRF24_get_status();
uint8_t NRF24_flush_rx();
uint8_t NRF24_flush_tx();
void NRF24_set_tx_addr(uint8_t * addr);
void NRF24_set_rx_addr(uint8_t * addr ,uint8_t reg);
void NRF24_set_channel(uint8_t ch);
void NRF24_set_data_rate(uint8_t data_rate);
void NRF24_set_addr_width(uint8_t width);
void NRF24_set_pipe_payload_width(uint8_t pipe, uint8_t payload_width);
void NRF24_enable_auto_ack(uint8_t pipes);
void NRF24_enable_rx_addresses(uint8_t pipes);
void NRF24_setup_retransmission(uint8_t delay, uint8_t tries);

#endif // NRF24L01_LOWLEVEL_H
