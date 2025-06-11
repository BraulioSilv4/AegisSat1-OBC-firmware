#ifndef GPS_INTERFACE_H
#define GPS_INTERFACE_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project defines */
#include "projdefines.h"

/* Components Includes */
#include "components/GPS_component/GPS_component.h"

typedef struct {
    char time[TIME_LENGHT_GPGGA];         // UTC time, hhmmss.ss
    char latitude[LAT_LENGHT_GPGGA];      // Latitude, DDmm.mm
    char lat_dir;                         // 'N' or 'S'
    char longitude[LON_LENGHT_GPGGA];     // Longitude, DDDmm.mm
    char lon_dir;                         // 'E' or 'W'
    char altitude[ALT_LENGHT_GPGGA];      // Altitude in Meters  
    //char speed_knot[SPEED_KNOT_LENGHT_GPRMC]
} GPS_Data;

bool get_gps_data(GPS_Data *data);

#endif // GPS_INTERFACE_H
