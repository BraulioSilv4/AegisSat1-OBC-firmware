#include "tasks.h"

#include "interfaces/Tasks_interfaces/itf_comm.h"
#include "cmd_protocol.h"

#include "tasks/Common/Packets/data_packet.h"
#include "tasks/Common/Packet_buffers/GPS/gps_packet_buffer.h"
#include "tasks/Common/Packet_buffers/Housekeeping/housekeeping_packet_buffer.h"

#define PING_RESPONSE "PING"
#define NO_DATA_RSP "No data to be sent"
#define GPS_DATA 0x01
#define HK_DATA 0x02


void handle_send_data(uint8_t data_types, itf_radio_module_t * radio) {
    while(true) {
        data_packet_t data = {0};
        bool has_data = false;

        if (data_types & GPS_DATA) {
            gps_packet_t gps_data = {0};
            if( gps_read_packet(&gps_data, pdMS_TO_TICKS(100)) ) {
                has_data = true;
                memcpy(&data.gps, &gps_data, sizeof(gps_data_t));
            }
        }

        if (data_types & HK_DATA) {
            housekeeping_packet_t hk_data = {0};
            if (hk_read_packet( &hk_data, pdMS_TO_TICKS(100) )) {
                has_data = true;
                memcpy(&data.temperature, &hk_data.temperature, sizeof(temperature_t));
                memcpy(&data.humidity, &hk_data.humidity, sizeof(humidity_t));
                memcpy(&data.pressure, &hk_data.pressure, sizeof(pressure_t));
            }
        }

        if (has_data) {
            radio->send_data(radio, (uint8_t *) &data, sizeof(data), pdMS_TO_TICKS(100) );
        } else {
            radio->send_data(radio, (uint8_t *) NO_DATA_RSP, sizeof(NO_DATA_RSP), pdMS_TO_TICKS(100));
            break;
        };
    }

    radio->start_listening(radio);
}

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
            handle_send_data(cmd->payload[0],radio);
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
