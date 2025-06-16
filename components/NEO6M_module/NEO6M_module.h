#ifndef NEO6M_MODULE_H
#define NEO6M_MODULE_H

/* Kernel Includes */
#include "FreeRTOS.h"

/* Project Defines */
#include "projdefines.h"

/* UART Include */
#include "UART_component/uart_component.h"

/* Interfaces to implement */
#include "interfaces/Components_interfaces/itf_gps_module.h"


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

typedef struct NEO6M_module {
    itf_gps_module_t gps_interface;

    /* GPS UART Buffer */
    char line[GPS_BUFFER_SIZE];

    /* Implementation State */
    bool initialized;
} NEO6M_module_t;

void NEO6M_module_create(NEO6M_module_t *this);

bool NEO6M_init(itf_gps_module_t *this, TickType_t timeout);
bool NEO6M_get_data(itf_gps_module_t *this, gps_data_t *data, TickType_t timeout);

#endif // NEO6M_MODULE_H
