#ifndef ITF_RADIO_H
#define ITF_RADIO_H

#include "FreeRTOS.h"

#include "projdefines.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct itf_radio_module itf_radio_module_t;

struct itf_radio_module {
    void (*init)(itf_radio_module_t *this);
    void (*start_listening)(itf_radio_module_t *this);
    void (*stop_listening)(itf_radio_module_t *this);
    bool (*data_available)(itf_radio_module_t *this);
    bool (*send_data)(itf_radio_module_t *this, uint8_t *data, uint8_t length, TickType_t timeout);
    bool (*receive_data)(itf_radio_module_t *this, uint8_t *buffer, uint8_t length);
};

#endif /* ITF_RADIO_H */
