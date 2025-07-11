#ifndef NRF24L01_CONFIG_H
#define NRF24L01_CONFIG_H

#define NRF24_PAYLOAD_SIZE 32
#define NRF24_CHANNEL 76
#define NRF24_TX_ADDR "00001"
#define NRF24_PIPE_0_ADDR NRF24_TX_ADDR
#define NRF24_PIPE_1_ADDR "00002"
#define NRF24_SPI_TIMEOUT pdMS_TO_TICKS(100)
#define NRF24_RETR_DELAY 0x30
#define NRF24_RETR_TRIES 15

#endif // NRF24L01_CONFIG_H
