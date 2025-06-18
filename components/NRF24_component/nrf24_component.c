#include "nrf24_component.h"


bool NRF24_data_available() {
    uint8_t status = NRF24_get_status();
    return status & RX_DR;
}

void NRF24_stop_listening() {
    CE_LOW();
    uint8_t config = NRF24_read_register(CONFIG);
    NRF24_write_register(CONFIG, config & ~PRIM_RX);
    NRF24_flush_rx();
}

bool NRF24_send_data(uint8_t * data, uint8_t length, TickType_t timeout) {
    NRF24_stop_listening();
 
    NRF24_flush_tx();
    NRF24_write_payload(data, length);

    NRF24_clear_flags();

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
    NRF24_clear_flags();
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
    NRF24_clear_flags();
    NRF24_flush_rx();
    NRF24_flush_tx();
    NRF24_setup_retransmission(NRF24_RETR_DELAY, NRF24_RETR_TRIES);
    NRF24_enable_auto_ack(NRF24_PIPE_0);
    NRF24_set_addr_width(NRF24_ADDR_WIDTH_5);
    NRF24_enable_rx_addresses(NRF24_PIPE_0);
    NRF24_set_pipe_payload_width(NRF24_PIPE_0, NRF24_PAYLOAD_SIZE);
    NRF24_set_rx_addr(NRF24_PIPE_0_ADDR, RX_ADDR_P0);
    NRF24_set_tx_addr(NRF24_TX_ADDR);
    NRF24_set_channel(NRF24_CHANNEL);
    NRF24_set_data_rate(NRF24_1MBPS_DATA_RATE); 
    NRF24_start_listening();
}
