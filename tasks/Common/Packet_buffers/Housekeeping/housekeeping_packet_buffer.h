#ifndef HK_PACKET_BUFFER_H
#define HK_PACKET_BUFFER_H

/* Kernel Includes */
#include "FreeRTOS.h"
#include "semphr.h"

/* Packet Structure Include */
#include "tasks/Common/Packets/housekeeping_packet.h"

#define HK_PACKET_NUMBER 1

extern housekeeping_packet_t hk_packets[HK_PACKET_NUMBER];
extern uint8_t hk_next_packet_index;

extern SemaphoreHandle_t hk_buffer_mutex;

#endif // HK_PACKET_BUFFER_H
