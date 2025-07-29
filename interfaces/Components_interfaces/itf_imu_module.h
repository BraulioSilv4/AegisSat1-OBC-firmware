#ifndef ITF_IMU_H
#define ITF_IMU_H

#include "FreeRTOS.h"
#include "projdefines.h"

typedef struct {
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
    int16_t mag_x, mag_y, mag_z;
    int16_t quat_x, quat_y, quat_z, quat_w;
    

} imu_data_t; 

typedef struct itf_imu_module itf_imu_module_t;

struct itf_imu_module {
    bool (*init)(itf_imu_module_t *this, TickType_t timeout);
    bool (*read)(itf_imu_module_t *this, imu_data_t *data, TickType_t timeout);
    bool (*reset)(itf_imu_module_t *this, TickType_t timeout);
};

#endif
