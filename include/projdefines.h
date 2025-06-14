#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

/* C Defines */
#include "stdint.h"
#include "stdbool.h"

/* MSP430FR2433 HAL */
#include "msp430fr2433.h"

/****************************************************************************************
* I2C Defines ***************************************************************************
*****************************************************************************************/

/* AHT20 defines */
#define AHT20                   0x38
#define AHT20_CALIBRATION_EN    0x08
#define AHT20_READ_STATUS       0b01000000
/* AHT20 Regs/Commands */
#define AHT20_STATUS_CMD        0x71
#define AHT20_INIT_CMD          0xBE
#define AHT20_INIT_ARG_1        0x08
#define AHT20_INIT_ARG_2        0x00
#define AHT20_TIRG_MEASURE_CMD  0xAC
#define AHT20_TRIG_ARG_1        0x33
#define AHT20_TRIG_ARG_2        0x00

/* BMP280 defines */
#define BMP280                  0x77
#define BMP280_CHIP_ID          0x58
#define BMP280_MEASURING_BIT    0x08
#define BMP280_CONFIG_MASK      0xFD    // Mask to use when writing to the config register
#define BMP280_MAX_READ_TRIES   5
/* BMP280 Regs */
#define BMP280_CHIP_ID_R        0xD0    // The “id” register contains the chip identification number chip_id[7:0], which is 0x58
#define BMP280_RESET_W          0xE0    // The “reset” register contains the soft reset word reset[7:0]. If the value 0xB6 is written to the register, the device is reset using the complete power-on-reset procedure
#define BMP280_STATUS_R         0xF3    // The “status” register contains two bits which indicate the status of the device
#define BMP280_CTRL_MEAS_RW     0xF4    // The “ctrl_meas” register sets the data acquisition options of the device. 
#define BMP280_CONFIG_RW        0xF5
#define BMP280_PRESS_MSB_R      0xF7
#define BMP280_PRESS_LSB_R      0xF8
#define BMP280_PRESS_XLSB_R     0xF9
#define BMP280_TEMP_MSB_R       0xFA
#define BMP280_TEMP_LSB_R       0xFB
#define BMP280_TEMP_XLSB_R      0xFC
/* BMP280 Trimming values */
#define BMP280_DIG_T1_LSB_R     0x88    // Burst read 24 bytes from here to get all temperature and pressure trimming values
#define BMP280_DIG_P1_LSB_R     0x8E    // Burst read 18 bytes from here to get all pressure trimming values
#define BMP280_TEMP_TRIM        3       // Total 16 bit trimming values for temperature
#define BMP280_PRESS_TRIM       9       // Total 16 bit trimming values for pressure
#define BMP280_TRIM_BYTES       24      // Total bytes for all trimming values


/* I2C driver defines */
#define DUMMY_I2C_ADDR          0x70
#define MAX_I2C_BUFFER_SIZE     20

/* I2C max failed attempts */
#define I2C_MAX_ATTEMPTS        5

/* I2C clock divisor */
#define I2C_CLOCK_DIVISOR       (SMCLK_FREQ_MHZ*10)

/****************************************************************************************
* End of I2C Defines ********************************************************************
*****************************************************************************************/

/****************************************************************************************
* Tasks Defines *************************************************************************
*****************************************************************************************/

/* GPS task */
#define GPGGA_PATTERN "$GPGGA,"
#define TIME_LENGHT_GPGGA   11    
#define LAT_LENGHT_GPGGA    10
#define LON_LENGHT_GPGGA    11
#define ALT_LENGHT_GPGGA    8

/****************************************************************************************
* End of Tasks Defines ******************************************************************
*****************************************************************************************/


/* Ring Buffer defines */
#define RING_BUF_MAX_SIZE    100                // Size of GPS (GPGGA) sentence plus few extra bytes

/* Clocks defines */
#define MCLK_FREQ_MHZ        16                 // MCLK = 16MHz
#define SMCLK_FREQ_MHZ       8                  // SMCLK = 8MHz

/****************************************************************************************
* Project Macros ************************************************************************
*****************************************************************************************/
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define U16(msb, lsb) ((uint16_t)(((msb) << 8) | (lsb)))
#define S16(msb, lsb) ((int16_t)(((msb) << 8) | (lsb)))

#define INVALID_VALUE ~0

#endif // PROJECT_DEFINES_H
