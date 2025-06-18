#include "gps_packet_buffer.h"

gps_packet_t gps_packets[GPS_PACKETS_NUM];
uint8_t gps_next_packet_index = 0;
uint8_t gps_available_packets = 0;

SemaphoreHandle_t gps_buffer_mutex = NULL;

bool gps_read_packet(gps_packet_t *packet, TickType_t timeout) {
    if(!gps_buffer_mutex) return false;
    if(!(gps_available_packets > 0)) return false; 
    if(xSemaphoreTake(gps_buffer_mutex, timeout)) {
        if((gps_next_packet_index - 1) < 0) {
            gps_next_packet_index = GPS_PACKETS_NUM - 1;
        } else {
            gps_next_packet_index--;
        }
        *packet = gps_packets[gps_next_packet_index];
        gps_available_packets--;
        xSemaphoreGive(gps_buffer_mutex);
        return true;
    }
    return false;
}
