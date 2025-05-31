#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

/****************************************************************************************
* I2C Defines ***************************************************************************
*****************************************************************************************/

/* AHT20 defines */
#define AHT20                   0x38

/* BMP280 defines */
#define BMP280                  0x77
#define BMP280_CHIP_ID_CMD      0xD0

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

#endif // PROJECT_DEFINES_H
