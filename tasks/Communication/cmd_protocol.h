#ifndef COMMAND_PROTOCOL_H
#define COMMAND_PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>
#include "string_utils.h"

#define CMD_MAX_PAYLOAD_SIZE 30

typedef enum {
    CMD_NOP         = 0x00,
    CMD_PING        = 0x01,
    CMD_REBOOT      = 0x03,
    CMD_SEND_DATA   = 0x04,
} command_id_t;

typedef struct {
    command_id_t id;
    uint8_t length;
    uint8_t payload[CMD_MAX_PAYLOAD_SIZE];
} command_packet_t;

bool parse_command(const uint8_t * data, uint8_t len, command_packet_t *cmd);

#endif
