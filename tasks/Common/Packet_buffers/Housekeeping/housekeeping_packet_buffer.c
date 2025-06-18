#include "housekeeping_packet_buffer.h"

housekeeping_packet_t hk_packets[HK_PACKET_NUMBER];
uint8_t hk_next_packet_index = 0;
uint8_t hk_available_packets = 0;

SemaphoreHandle_t hk_buffer_mutex = NULL;

bool hk_read_packet(housekeeping_packet_t *packet, TickType_t timeout) {
    if(!hk_buffer_mutex) return false;
    if(!(hk_available_packets > 0)) return false; 
    if(xSemaphoreTake(hk_buffer_mutex, timeout)) {
        if((hk_next_packet_index - 1) < 0) {
            hk_next_packet_index = HK_PACKET_NUMBER - 1;
        } else {
            hk_next_packet_index--;
        }
        *packet = hk_packets[hk_next_packet_index];
        hk_available_packets--;
        xSemaphoreGive(hk_buffer_mutex);
        return true;
    }
    return false;
}
