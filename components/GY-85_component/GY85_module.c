#include "GY85_module.h"


bool GY85_init(itf_imu_module_t * this, TickType_t timeout) {
    return ITG3200_init(timeout) &&
          HMC5883L_init(timeout) &&
          ADXL345_init(timeout);
}

bool GY85_reset(itf_imu_module_t * this, TickType_t timeout) {
    return GY85_init(this,timeout);
}

bool GY85_read(itf_imu_module_t * this, imu_data_t *data, TickType_t timeout) {

    if (!ADXL345_read(&data->accel_x, &data->accel_y, &data->accel_z, timeout))
        return false;

    if (!ITG3200_read(&data->gyro_x,&data->gyro_y, &data->gyro_z, timeout)) 
        return false;
    
    if (!HMC5883L_read(&data->mag_x, &data->mag_y, &data->mag_z,timeout))
        return false;

    data->quat_x = 0;
    data->quat_y = 0;
    data->quat_z = 0;
    data->quat_w = 1;

    return true;
}

void GY85_module_create(GY85_module_t * module) {
    module->imu_interface.init = GY85_init;
    module->imu_interface.read = GY85_read;
    module->imu_interface.reset = GY85_reset;
}
