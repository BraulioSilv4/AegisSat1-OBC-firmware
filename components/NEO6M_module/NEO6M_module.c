#include "NEO6M_module.h"

static uint8_t calculate_checksum(const char *nmea) {
    uint8_t checksum = 0;
    const char *p = nmea + 1; // Skip $
    while(*p && *p != '*') {
        checksum ^= *p++;
    }
    return checksum;
}

static bool get_checksum_from_nmea(const char *nmea, uint8_t *out_checksum) {
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

static bool parse_nmea_gpgga(const char *nmea, gps_data_t *data) {
    if(!nmea || !data) return false;

    uint8_t checksum = calculate_checksum(nmea);
    uint8_t received_checksum;
    if(!get_checksum_from_nmea(nmea, &received_checksum)) return false;

    if(checksum != received_checksum) return false;

    char *token = strtok_single_char((char *)nmea, ',');
    uint8_t field = GPGGA;

    while(token) {
        switch(field) {
            case TIME: data->time = (uint32_t)string_to_int(token, TIME_LENGHT_GPGGA); break;   
            case LAT:  data->latitude = string_to_int(token, LAT_LENGHT_GPGGA); break;
            case LAT_DIR: data->lat_dir = token[0]; break;
            case LON:  data->longitude = string_to_int(token, LON_LENGHT_GPGGA); break;
            case LON_DIR: data->lon_dir = token[0]; break;
            case ALT:  data->altitude = (uint32_t)string_to_int(token, ALT_LENGHT_GPGGA); break;
        }
        token = strtok_single_char(NULL, ',');
        field++;
    }
    
    return true;
}   

bool NEO6M_init(itf_gps_module_t *this, TickType_t timeout) {
    NEO6M_module_t *neo6m = container_of(this, NEO6M_module_t, gps_interface);
    if(!neo6m->initialized) neo6m->initialized = true;
    return neo6m->initialized;
}

bool NEO6M_get_data(itf_gps_module_t *this, gps_data_t *data, TickType_t timeout) {
    NEO6M_module_t *neo6m = container_of(this, NEO6M_module_t, gps_interface);
    if(!uart_read_line_pattern(
        neo6m->line, 
        GPS_BUFFER_SIZE, 
        GPGGA_PATTERN, 
        timeout
    )) return false;
    return parse_nmea_gpgga(neo6m->line, data);
}

void NEO6M_module_create(NEO6M_module_t *this) {
    this->gps_interface.init        = NEO6M_init; 
    this->gps_interface.get_gps     = NEO6M_get_data;
    
    this->initialized = false;
}
