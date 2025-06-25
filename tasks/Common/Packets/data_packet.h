#ifndef DATA_PACKET_H
#define DATA_PACKET_H

/* Task Interface Include */
#include "interfaces/Tasks_interfaces/itf_gps.h"
#include "interfaces/Tasks_interfaces/itf_housekeeping.h"

typedef struct {
    gps_data_t gps;
    pressure_t pressure;
    humidity_t humidity;
    temperature_t temperature;
} data_packet_t;

#endif // DATA_PACKET_H
