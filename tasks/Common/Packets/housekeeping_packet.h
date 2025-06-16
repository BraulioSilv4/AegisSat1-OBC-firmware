#ifndef HK_PACKET_H
#define HK_PACKET_H

/* Task Interface Include */
#include "interfaces/Tasks_interfaces/itf_housekeeping.h"

typedef struct {
    pressure_t pressure;
    humidity_t humidity;
    temperature_t temperature;
} housekeeping_packet_t;

#endif // HK_PACKET_H
