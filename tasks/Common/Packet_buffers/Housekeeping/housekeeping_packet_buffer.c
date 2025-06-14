#include "housekeeping_packet_buffer.h"

housekeeping_packet_t hk_packets[HK_PACKET_NUMBER];
uint8_t hk_next_packet_index = 0;

SemaphoreHandle_t hk_buffer_mutex = NULL;
