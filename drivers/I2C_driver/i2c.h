#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

// RTOS includes
#include "FreeRTOS.h"
#include "semphr.h"

#include "msp430fr2433.h"
#include "projdefines.h"

#include "stdbool.h"
#include "stdint.h"

#include "string_utils.h"

//******************************************************************************
// General I2C State Machine ***************************************************
//******************************************************************************
typedef enum I2C_ModeEnum {
    IDLE_MODE,
    NACK_MODE,
    TX_REG_ADDRESS_MODE,
    RX_REG_ADDRESS_MODE,
    TX_DATA_MODE,
    RX_DATA_MODE,
    SWITCH_TO_RX_MODE,
    SWITCH_TO_TX_MODE,
    TIMEOUT_MODE
} I2C_Mode;

/* Semaphore to allow the use of I2C for a task */
extern SemaphoreHandle_t xI2CSemaphore; 

/* Semaphore to notify when a receive has been completed */
extern SemaphoreHandle_t xI2CDoneSemaphore;

/* ReceiveBuffer: Buffer used to receive data in the ISR
 * TransmitBuffer: Buffer used to transmit data in the ISR
 * */
extern uint8_t ReceiveBuffer[MAX_I2C_BUFFER_SIZE];
extern uint8_t TransmitBuffer[MAX_I2C_BUFFER_SIZE];

I2C_Mode I2C_Master_WriteReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t count);

I2C_Mode I2C_Master_WriteSlave(uint8_t dev_addr, uint8_t *reg_data, uint8_t count);

I2C_Mode I2C_Master_ReadReg(uint8_t dev_addr, uint8_t reg_addr, uint8_t count);

/*
 * Initializes the I2C hardware registers 
 * */
void init_I2C();

#endif  // I2C_DRIVER_H
