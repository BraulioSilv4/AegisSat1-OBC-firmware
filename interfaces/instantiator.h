#ifndef ITF_INSTANTIATOR_H
#define ITF_INSTANTIATOR_H

/* Tasks Interfaces Includes */
#include "Tasks_interfaces/itf_housekeeping.h"

/* Components Interfaces Includes */
#include "Components_interfaces/itf_humidity_sensor.h"
#include "Components_interfaces/itf_temp_sensor.h"

/* Components Implementations Includes */
#include "components/AHT20_component/AHT20_component.h"

void instantiate_interfaces();

HK_interface_t *get_hk_interface();

#endif // ITF_INSTANTIATOR_H
