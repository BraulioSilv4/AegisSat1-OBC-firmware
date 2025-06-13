#include "instantiator.h"

/* Tasks Interfaces */
static HK_interface_t hk_interface;

/* Compenents Implementations */
static AHT20_sensor_t aht20_sensor;

void instantiate_interfaces() {
    AHT20_sensor_create(&aht20_sensor);
    hk_interface.humidity_sensor = &aht20_sensor.hum_interface;
    hk_interface.temp_sensor     = &aht20_sensor.temp_interface;
}

HK_interface_t *get_hk_interface() {
    return &hk_interface;
}
