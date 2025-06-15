#include "instantiator.h"

/* Tasks Interfaces */
static HK_interface_t hk_interface;

/* Compenents Implementations */
static AHT20_sensor_t aht20_sensor;
static BMP280_sensor_t bmp280_sensor;
static BMP280_sensor_t bmp280_sensor_2;

void instantiate_interfaces() {
    /* Components Instantiation */
    AHT20_sensor_create(&aht20_sensor);
    BMP280_sensor_create_32(&bmp280_sensor);
    BMP280_sensor_create_linear(&bmp280_sensor_2);

    /* Task Interface Wiring */
    hk_interface.humidity_sensor    = &aht20_sensor.hum_interface;
    hk_interface.temperature_sensor = &aht20_sensor.temperature_interface;
    hk_interface.pressure_sensor    = &bmp280_sensor.pressure_interface;
    hk_interface.alternate          = &bmp280_sensor_2.pressure_interface;
}

HK_interface_t *get_hk_interface() {
    return &hk_interface;
}
