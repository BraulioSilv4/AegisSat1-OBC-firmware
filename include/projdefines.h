#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

/* C Defines */
#include "stdint.h"
#include "stdbool.h"

/* MSP430FR2433 HAL */
#include "msp430fr2433.h"


/****************************************************************************************
* NRF24L01 defines **********************************************************************
*****************************************************************************************/

// NRF24 commands
#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0
#define FLUSH_TX 0xE1
#define FLUSH_RX 0xE2
#define REUSE_TX_PL 0xE3
#define ACTIVATE 0x50
#define R_RX_PL_WID 0x60
#define READ_REGISTER(reg) ((reg) & 0x1F)
#define WRITE_REGISTER(reg) ((reg) & 0x1F | 0x20)
#define W_TX_PAYLOAD_NO_ACK 0x00
#define NOP 0xFF

// NRF24 registers
#define CONFIG 0x00
#define EN_AA 0x01          // Auto Ack register
#define EN_RXADDR 0x02      // RX addresses
#define SETUP_AW 0x03       // Address Widths
#define SETUP_RETR 0x04     // Setup for automatic retransmission
#define RF_CH 0x05          // RF Channel
#define RF_SETUP 0x06    
#define STATUS 0x07 
#define OBSERVE_TX 0x8
#define CD 0x09
#define RX_ADDR_P0 0X0A
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P5 0x0F
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16
#define FIFO_STATUS 0x17

//Configuration register bits
#define MASK_RX_DR 0x40
#define MASK_TX_DS 0x20
#define MASK_MAX_RT 0x10
#define EN_CRC 0x08
#define CRCO 0x04
#define PWR_UP 0x02
#define PRIM_RX 0x01

//NRF24 status register bits
#define RX_DR 0x40   
#define TX_DS 0x20
#define MAX_RT 0x10
#define RX_P_NO 0x0E
#define TX_FULL 0x01

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
#define GPS_BUFFER_SIZE         75
#define GPGGA_PATTERN           "$GPGGA,"
#define TIME_LENGHT_GPGGA       9    
#define LAT_LENGHT_GPGGA        10
#define LON_LENGHT_GPGGA        10
#define ALT_LENGHT_GPGGA        4

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
