#ifndef GPS_INTERFACE_H
#define GPS_INTERFACE_H

#include "projdefines.h"
#include "string_utils.h"

typedef enum {
    GPGGA,          // Log header
    TIME,           // UTC time status of position (hours/minutes/seconds/ decimal seconds)
    LAT,            // Latitude (DDmm.mm)
    LAT_DIR,        // Latitude direction (N = North, S = South)
    LON,            // Longitude (DDDmm.mm)
    LON_DIR,        // Longitude direction (E = East, W = West)
    QUALITY,        // GPS quality indicators
    NUM_SATS,       // Number of satellites in use. May be different to the number in view
    HDOP,           // Horizontal dilution of precision
    ALT,            // Antenna altitude above/below mean sea level
    ALT_UNIT,       // Units of antenna altitude (M = metres)
    UNDULATION,     // Undulation - the relationship between the geoid and the WGS84 ellipsoid
    U_UNIT,         // Units of undulation (M = metres)
    AGE,            // Age of correction data (in seconds). The maximum age reported here is limited to 99 seconds.
    STN_ID          // Differential base station ID
} GPGGA_Fields;

typedef struct {
    char time[TIME_LENGHT_GPGGA];         // UTC time, hhmmss.ss
    char latitude[LAT_LENGHT_GPGGA];                         // Latitude, DDmm.mm
    char lat_dir;                         // 'N' or 'S'
    char longitude[LON_LENGHT_GPGGA];                        // Longitude, DDDmm.mm
    char lon_dir;                         // 'E' or 'W'
    char altitude[ALT_LENGHT_GPGGA];                         // Altitude in Meters  
} GPGGA_Data;

bool parse_nmea_gpgga(const char *sentence, GPGGA_Data *data);

#endif // GPS_INTERFACE_H
