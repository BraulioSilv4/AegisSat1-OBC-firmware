#ifndef HK_PACKET_H
#define HK_PACKET_H

typedef struct {
    uint32_t pressure;
    int16_t temperature;
    int16_t humidity;
} housekeeping_packet_t;

#endif // HK_PACKET_H
