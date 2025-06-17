#include "nrf24_component.h"

#define SPI_TIMEOUT pdMS_TO_TICKS(100)
#define ADDRESS "00001"
#define PAYLOAD_SIZE 32

uint8_t NRF24_read_register(uint8_t reg) {
    uint8_t tx[2] = { READ_REGISTER(reg), NOP };
    uint8_t rx[2];
    spi_transfer(tx, rx, 2, SPI_TIMEOUT);
    return rx[1];
}

void NRF24_read_register_multi(uint8_t reg, uint8_t *data) {
    uint8_t tx[6], rx[6];
    tx[0] = READ_REGISTER(reg);          // or READ_REGISTER(reg)
    setmem(&tx[1], NOP, 5);
    spi_transfer(tx, rx, 6, SPI_TIMEOUT);
    memcpy(data, &rx[1], 5);
}

void  NRF24_write_register(uint8_t reg, uint8_t data) {
    uint8_t tx[2] = { WRITE_REGISTER(reg), data };
    uint8_t rx[2];
    spi_transfer(tx, rx, 2, SPI_TIMEOUT);
}

uint8_t NRF24_get_status() {
    uint8_t tx = NOP; uint8_t rx;
    spi_transfer(&tx, &rx, 1, SPI_TIMEOUT);
    return rx;
}

uint8_t NRF24_flush_rx() {
    uint8_t tx = FLUSH_RX; uint8_t rx;
    spi_transfer(&tx, &rx, 1, SPI_TIMEOUT);
    return rx;
}

uint8_t NRF24_flush_tx() {
    uint8_t tx = FLUSH_TX; uint8_t rx;
    spi_transfer(&tx, &rx, 1, SPI_TIMEOUT);
    return rx;
}

void NRF24_set_tx_addr(uint8_t * addr) {
    uint8_t tx[6] = { WRITE_REGISTER(TX_ADDR) };
    uint8_t rx[6];
    cpymem(&tx[1], addr, 5);
    spi_transfer(tx, rx, 6, SPI_TIMEOUT);
}

void NRF24_set_rx_addr(uint8_t * addr ,uint8_t reg) {
    uint8_t tx[6] = {WRITE_REGISTER(reg)};
    uint8_t rx[6];
    cpymem(&tx[1], addr, 5);
    spi_transfer(tx, rx, 6, SPI_TIMEOUT);
}

bool NRF24_data_available() {
    uint8_t status = NRF24_get_status();
    return status & RX_DR;
}

void NRF24_write_payload(uint8_t * data, uint8_t length) {
    uint8_t tx[PAYLOAD_SIZE+1];
    uint8_t rx[PAYLOAD_SIZE+1];
    tx[0] = W_TX_PAYLOAD;
    cpymem(&tx[1], data, PAYLOAD_SIZE);
    spi_transfer(tx, rx, PAYLOAD_SIZE+1, SPI_TIMEOUT);
}

void NRF24_read_payload(uint8_t * buffer, uint8_t length) {
    uint8_t tx[PAYLOAD_SIZE+1];
    uint8_t rx[PAYLOAD_SIZE+1];
    tx[0] = R_RX_PAYLOAD;
    setmem(&tx[1], NOP, PAYLOAD_SIZE);
    spi_transfer(tx, rx, PAYLOAD_SIZE + 1, SPI_TIMEOUT);
    cpymem(buffer, &rx[1], PAYLOAD_SIZE);
}

void NRF24_stop_listening() {
    CE_LOW();
    uint8_t config = NRF24_read_register(CONFIG);
    NRF24_write_register(CONFIG, config & ~PRIM_RX);
    NRF24_flush_rx();
}

bool NRF24_send_data(uint8_t * data, uint8_t length, TickType_t timeout) {
    NRF24_stop_listening(); // switch to tx mode
 
    NRF24_flush_tx();
    NRF24_write_payload(data, length);

    CE_HIGH();
    vTaskDelay(pdMS_TO_TICKS(1));
    CE_LOW();

    TickType_t start = xTaskGetTickCount();
    while ((xTaskGetTickCount() - start) < timeout) {
        uint8_t status = NRF24_get_status();
        if (status & TX_DS) {
            NRF24_write_register(STATUS, TX_DS); 
            return true;
        } else if (status & MAX_RT) {
            NRF24_flush_tx();
            NRF24_write_register(STATUS, MAX_RT);
            return false;
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    NRF24_flush_tx();
    return false;
}

bool NRF24_attempt_receive(uint8_t * buffer, uint8_t length) {
    if (!NRF24_data_available()) return false;
    NRF24_read_payload(buffer, length);
    NRF24_write_register(STATUS, RX_DR);
    return true;
}

void NRF24_start_listening() {
    CE_LOW();
    uint8_t config = NRF24_read_register(CONFIG);
    NRF24_write_register(CONFIG, config | PRIM_RX);
    CE_HIGH();
}   

void NRF24_Init() {
    CE_LOW();
    const uint8_t configuration_bits = PWR_UP | MASK_RX_DR | MASK_TX_DS | MASK_MAX_RT | EN_CRC | PRIM_RX;
    NRF24_write_register(CONFIG, configuration_bits);
    NRF24_write_register(STATUS, RX_DR | TX_DS | MAX_RT);
    NRF24_flush_rx();
    NRF24_flush_tx();

    NRF24_write_register(EN_AA, 0x3F);

    NRF24_write_register(SETUP_AW, 0x03);

    NRF24_write_register(EN_RXADDR, 0x01);



    NRF24_write_register(RX_PW_P0,PAYLOAD_SIZE);


    // Set rx and tx addresses.
    NRF24_set_rx_addr(ADDRESS, RX_ADDR_P0);
    NRF24_set_tx_addr(ADDRESS);

    NRF24_write_register(RF_CH,76);
    NRF24_write_register(RF_SETUP,0x06);

    uint8_t probe[5];
    NRF24_read_register_multi(RX_ADDR_P0, probe);

    NRF24_start_listening();
}
