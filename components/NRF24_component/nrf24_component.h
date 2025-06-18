// NRF24_component.h

#ifndef NRF24_COMPONENT_H
#define NRF24_COMPONENT_H

#include "Components_interfaces/itf_radio_module.h"

typedef struct {
    itf_radio_module_t radio_interface;
} NRF24_module_t;

void NRF24_module_create(NRF24_module_t *module);

#endif /* NRF24_COMPONENT_H */
