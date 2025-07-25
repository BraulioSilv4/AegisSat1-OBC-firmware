#ifndef GPS_PACKET_BUFFER_H
#define GPS_PACKET_BUFFER_H

/* Kernel Includes */
#include "FreeRTOS.h"
#include "semphr.h"

/* Packet Structure Include */
#include "tasks/Common/Packets/gps_packet.h"

#define GPS_PACKETS_NUM     4

extern gps_packet_t gps_packets[GPS_PACKETS_NUM];
extern uint8_t gps_next_packet_index;
extern uint8_t gps_available_packets;

extern SemaphoreHandle_t gps_buffer_mutex;

bool gps_read_packet(gps_packet_t *packet, TickType_t timeout);

#endif // GPS_PACKET_BUFFER_H
