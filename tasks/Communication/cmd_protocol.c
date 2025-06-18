#include "cmd_protocol.h"

bool parse_command(const uint8_t *data, uint8_t len, command_packet_t *cmd) {
    if (len < 2 || len > CMD_MAX_PAYLOAD_SIZE + 2)
        return false;

    cmd->id = (command_id_t)data[0];
    cmd->length = data[1];

    if (cmd->length > CMD_MAX_PAYLOAD_SIZE || cmd->length > (len - 2))
        return false;

    cpymem(cmd->payload, &data[2], cmd->length);
    return true;
}
