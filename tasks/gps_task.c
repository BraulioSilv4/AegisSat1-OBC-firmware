#include "tasks.h"

void vGet_GPS(void *pvParameters) {
    char line[100];

    while(1) {
        if(uart_read_line_pattern(line, sizeof(line), "$GPGGA")) {
            // Parse NMEA sentence here
            while(1);
        }
    }
}
