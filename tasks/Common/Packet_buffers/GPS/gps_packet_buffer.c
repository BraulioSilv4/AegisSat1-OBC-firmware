#include "gps_packet_buffer.h"

gps_packet_t gps_packets[GPS_PACKETS_NUM];
uint8_t gps_next_packet_index = 0;

SemaphoreHandle_t gps_buffer_mutex = NULL;
