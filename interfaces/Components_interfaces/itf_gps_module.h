#ifndef ITF_GPS_H
#define ITF_GPS_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project Defines */
#include "projdefines.h"

typedef struct {
    uint32_t time;              // UTC time, hhmmss.ss (13210800 = 132108.00)
    int32_t latitude;           // Latitude, DDmm.mm (384535927 = 3845.35927)
    char lat_dir;               // 'N' or 'S' 
    int32_t longitude;          // Longitude, DDDmm.mm (009069387 = 00906.93870)
    char lon_dir;               // 'E' or 'W'
    uint32_t altitude;          // Altitude in Meters (503 = 50.3)
    //char speed_knot[SPEED_KNOT_LENGHT_GPRMC]
} gps_data_t;

typedef struct itf_gps_module itf_gps_module_t;

struct itf_gps_module {
    bool (*init)(itf_gps_module_t *this, TickType_t timeout);
    bool (*get_gps)(itf_gps_module_t *this, gps_data_t *data, TickType_t timeout);
};

#endif
