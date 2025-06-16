#ifndef GPS_PACKET_H
#define GPS_PACKET_H

/* Task Interface Include */
#include "interfaces/Tasks_interfaces/itf_gps.h"

typedef struct {
    gps_data_t data;
    bool valid;
} gps_packet_t;

#endif // GPS_PACKET_H
