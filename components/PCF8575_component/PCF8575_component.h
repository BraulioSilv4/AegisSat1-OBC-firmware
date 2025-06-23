#ifndef PCF8575_COMPONENT_H
#define PCF8575_COMPONENT_H

/* Kernel Include */
#include "FreeRTOS.h"

/* I2C Includes */
#include "I2C_component/I2C_component.h"

/* Project Defines */
#include "projdefines.h"

typedef uint16_t IO_expander_value_t; 

typedef struct itf_gpio_expander itf_gpio_expander_t;

typedef enum {
    P00 = 0x0001,
    P01 = 0x0002,
    P02 = 0x0004,
    P03 = 0x0008,
    P04 = 0x0010,
    P05 = 0x0020,
    P06 = 0x0040,
    P07 = 0x0080,
    P10 = 0x0100,
    P11 = 0x0200,
    P12 = 0x0400,
    P13 = 0x0800,
    P14 = 0x1000,
    P15 = 0x2000,
    P16 = 0x4000,
    P17 = 0x8000
} IOPort_t;

bool PCF8575_set_gpio(IO_expander_value_t set, TickType_t timeout);
bool PCF8575_read_gpio(IO_expander_value_t *out, TickType_t timeout);

#endif // PCF8575_COMPONENT_H
