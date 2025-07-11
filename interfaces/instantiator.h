#ifndef ITF_INSTANTIATOR_H
#define ITF_INSTANTIATOR_H

/* Tasks Interfaces Includes */
#include "Tasks_interfaces/itf_housekeeping.h"
#include "Tasks_interfaces/itf_gps.h"
#include "Tasks_interfaces/itf_comm.h"

/* Components Interfaces Includes */
#include "Components_interfaces/itf_humidity_sensor.h"
#include "Components_interfaces/itf_temp_sensor.h"
#include "Components_interfaces/itf_pressure_sensor.h"
#include "Components_interfaces/itf_gps_module.h"
#include "Components_interfaces/itf_radio_module.h"

/* Components Implementations Includes */
#include "components/AHT20_component/AHT20_component.h"
#include "components/BMP280_component/BMP280_component.h"
#include "components/NEO6M_module/NEO6M_module.h"
#include "components/NRF24_component/NRF24_component.h" 

void instantiate_interfaces();

HK_interface_t *get_hk_interface();
gps_interface_t *get_gps_interface();
comm_interface_t *get_comm_interface(); 

#endif // ITF_INSTANTIATOR_H
