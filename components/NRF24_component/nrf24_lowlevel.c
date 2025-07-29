#include "nrf24_lowlevel.h"


void NRF24_write_register(uint8_t reg, uint8_t data) {
    uint8_t tx[2] = { WRITE_REGISTER(reg), data };
    uint8_t rx[2];
    spi_transfer(tx, rx, 2, NRF24_SPI_TIMEOUT);
}

uint8_t NRF24_read_register(uint8_t reg) {
    uint8_t tx[2] = { READ_REGISTER(reg), NOP };
    uint8_t rx[2];
    spi_transfer(tx, rx, 2, NRF24_SPI_TIMEOUT);
    return rx[1];
}

void NRF24_write_payload(uint8_t * data, uint8_t length) {
    uint8_t tx[NRF24_PAYLOAD_SIZE+1];
    uint8_t rx[NRF24_PAYLOAD_SIZE+1];
    tx[0] = W_TX_PAYLOAD;
    cpymem(&tx[1], data, NRF24_PAYLOAD_SIZE);
    spi_transfer(tx, rx, NRF24_PAYLOAD_SIZE+1, NRF24_SPI_TIMEOUT);
}

void NRF24_read_payload(uint8_t * buffer, uint8_t length) {
    uint8_t tx[NRF24_PAYLOAD_SIZE+1];
    uint8_t rx[NRF24_PAYLOAD_SIZE+1];
    tx[0] = R_RX_PAYLOAD;
    setmem(&tx[1], NOP, NRF24_PAYLOAD_SIZE);
    spi_transfer(tx, rx, NRF24_PAYLOAD_SIZE + 1, NRF24_SPI_TIMEOUT);
    cpymem(buffer, &rx[1], NRF24_PAYLOAD_SIZE);
}

void NRF24_clear_flags() {
    NRF24_write_register(STATUS,RX_DR | TX_DS | MAX_RT);
}

uint8_t NRF24_get_status() {
    uint8_t tx = NOP; uint8_t rx;
    spi_transfer(&tx, &rx, 1, NRF24_SPI_TIMEOUT);
    return rx;
}

uint8_t NRF24_flush_rx() {
    uint8_t tx = FLUSH_RX; uint8_t rx;
    spi_transfer(&tx, &rx, 1, NRF24_SPI_TIMEOUT);
    return rx;
}

uint8_t NRF24_flush_tx() {
    uint8_t tx = FLUSH_TX; uint8_t rx;
    spi_transfer(&tx, &rx, 1, NRF24_SPI_TIMEOUT);
    return rx;
}

void NRF24_set_tx_addr(uint8_t * addr) {
    uint8_t tx[6] = { WRITE_REGISTER(TX_ADDR) };
    uint8_t rx[6];
    cpymem(&tx[1], addr, 5);
    spi_transfer(tx, rx, 6, NRF24_SPI_TIMEOUT);
}

void NRF24_set_rx_addr(uint8_t * addr ,uint8_t reg) {
    uint8_t tx[6] = {WRITE_REGISTER(reg)};
    uint8_t rx[6];
    cpymem(&tx[1], addr, 5);
    spi_transfer(tx, rx, 6, NRF24_SPI_TIMEOUT);
}

void NRF24_set_channel(uint8_t ch) {
    NRF24_write_register(RF_CH, ch);
}

void NRF24_set_data_rate(uint8_t data_rate) {
    NRF24_write_register(RF_SETUP, data_rate | 0x06);
}

void NRF24_set_addr_width(uint8_t width) {
    NRF24_write_register(SETUP_AW, width);  
}

void NRF24_set_pipe_payload_width(uint8_t pipe, uint8_t payload_width) {
    switch (pipe) {
        case NRF24_PIPE_0:
            NRF24_write_register(RX_PW_P0, payload_width);
            break;
        case NRF24_PIPE_1:
            NRF24_write_register(RX_PW_P1, payload_width);
            break;
        case NRF24_PIPE_2:
            NRF24_write_register(RX_PW_P2, payload_width);
            break;
        case NRF24_PIPE_3:
            NRF24_write_register(RX_PW_P3, payload_width);
            break;
        case NRF24_PIPE_4:
            NRF24_write_register(RX_PW_P4, payload_width);
            break;
        case NRF24_PIPE_5:
            NRF24_write_register(RX_PW_P5, payload_width);
            break;
        default: 
            break;  
    }
}

void NRF24_enable_auto_ack(uint8_t pipes) {
    NRF24_write_register(EN_AA, pipes);
}

void NRF24_enable_rx_addresses(uint8_t pipes) {
      NRF24_write_register(EN_RXADDR, pipes);
}

void NRF24_setup_retransmission(uint8_t delay, uint8_t tries) {
    NRF24_write_register(SETUP_RETR, (delay << 4) | tries);
}
