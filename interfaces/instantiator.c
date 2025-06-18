#include "instantiator.h"

/* Tasks Interfaces */
static HK_interface_t hk_interface;
static gps_interface_t gps_inteface;
static comm_interface_t comm_interface; 

/* Compenents Implementations */
static AHT20_sensor_t aht20_sensor;
static BMP280_sensor_t bmp280_sensor;
static NEO6M_module_t neo6m_module;
static NRF24_module_t nrf24_module; 

void instantiate_interfaces() {
    /* Components Instantiation */
    AHT20_sensor_create(&aht20_sensor);
    BMP280_sensor_create(&bmp280_sensor);
    NEO6M_module_create(&neo6m_module);
    NRF24_module_create(&nrf24_module);

    /* Task Interface Wiring */
    hk_interface.humidity_sensor    = &aht20_sensor.hum_interface;
    hk_interface.temperature_sensor = &aht20_sensor.temperature_interface;
    hk_interface.pressure_sensor    = &bmp280_sensor.pressure_interface;
    gps_inteface.gps_module         = &neo6m_module.gps_interface;
    comm_interface.radio_module = &nrf24_module.radio_interface;
}

HK_interface_t *get_hk_interface() {
    return &hk_interface;
}

gps_interface_t *get_gps_interface() {
    return &gps_inteface;
}

comm_interface_t *get_comm_interface() { 
    return &comm_interface;
}