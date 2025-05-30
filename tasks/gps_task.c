#include "tasks.h"

#include "GPS_interface.h"

void vGet_GPS(void *pvParameters) {
    char line[75];
    GPGGA_Data gps_data;

    while(1) {
        if(uart_read_line_pattern(line, sizeof(line), "$GPGGA")) {
            // Parse NMEA sentence here
            parse_nmea_gpgga(line, &gps_data);

            // Send pointer to GPS queue? 
        }
    }
}
