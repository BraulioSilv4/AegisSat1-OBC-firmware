#include "tasks.h"

#include "interfaces/Tasks_interfaces/itf_comm.h"
#include "cmd_protocol.h"

#define PING_RESPONSE "PING"

void handle_command(const command_packet_t * cmd, itf_radio_module_t * radio) {
    switch(cmd->id) {
        case CMD_PING:  
            radio->send_data(radio, (uint8_t *) PING_RESPONSE, sizeof(PING_RESPONSE), pdMS_TO_TICKS(100));
            radio->start_listening(radio);
            break;
        case CMD_REBOOT:
            //TODO
            break;
        case CMD_SEND_DATA:
            //TODO
            break;
        default:
            break;
    }
}

void comms_task(void *pvParameter) {
    comm_interface_t *itf = (comm_interface_t *)pvParameter;
    itf_radio_module_t *radio = itf->radio_module;
    
    uint8_t buffer[CMD_MAX_PAYLOAD_SIZE+2];
    command_packet_t cmd;

    radio->init(radio);

    radio->start_listening(radio);

    while (true) {
        if (radio->receive_data(radio,buffer,sizeof(buffer))) {
            if (parse_command(buffer,sizeof(buffer),&cmd)) {
                handle_command(&cmd,radio);
            } 
        }        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
