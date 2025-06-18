// itf_radio.h

#ifndef ITF_COMM_INTERFACE_H
#define ITF_COMM_INTERFACE_H

#include "Components_interfaces/itf_radio_module.h"

typedef struct {
    itf_radio_module_t *radio_module;
} comm_interface_t;

#endif /* ITF_COMM_INTERFACE_H */
