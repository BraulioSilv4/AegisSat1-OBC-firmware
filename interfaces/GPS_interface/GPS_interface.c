#include "GPS_interface.h"

uint8_t calculate_checksum(const char *nmea) {
    uint8_t checksum = 0;
    const char *p = nmea + 1; // Skip $
    while(*p && *p != '*') {
        checksum ^= *p++;
    }
    return checksum;
}

bool get_checksum_from_nmea(const char *nmea, uint8_t *out_checksum) {
    const char *star = find_first_char(nmea, '*');
    if(!star || string_length(star) < 2) return false;
    char checksum[2];
    checksum[0] = star[1];
    checksum[1] = star[2];
    if(hexstr_to_byte(checksum, out_checksum)) {
        return true;
    } else {
        return false;
    }
}

bool parse_nmea_gpgga(const char *nmea, GPGGA_Data *data) {
    if(!nmea || !data) return false;
    int cmp_ret = compare_string(nmea, GPGGA_PATTERN, string_length(GPGGA_PATTERN));
    if(cmp_ret != 0) {
        return false;
    }

    uint8_t checksum = calculate_checksum(nmea);
    uint8_t received_checksum;
    if(!get_checksum_from_nmea(nmea, &received_checksum)) return false;

    if(checksum != received_checksum) return false;

    char *token = strtok_single_char((char *)nmea, ',');
    uint8_t field = GPGGA;

    while(token) {
        switch(field) {
            case TIME: copy_string(data->time, token, sizeof(data->time) - 1); break;   
            case LAT:  copy_string(data->latitude, token, sizeof(data->latitude) - 1); break;
            case LAT_DIR: data->lat_dir = token[0]; break;
            case LON:  copy_string(data->longitude, token, sizeof(data->longitude) - 1); break;
            case LON_DIR: data->lon_dir = token[0]; break;
            case ALT:  copy_string(data->altitude, token, sizeof(data->altitude) - 1); break;
        }
        token = strtok_single_char(NULL, ',');
        field++;
    }
    
    return true;
}   
