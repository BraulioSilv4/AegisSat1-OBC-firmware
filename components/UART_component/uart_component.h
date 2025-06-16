#ifndef UART_COMPONENT_H
#define UART_COMPONENT_H

/* Driver Includes */
#include "UART_driver/uart.h"

/* Utils Includes */
#include "string_utils.h"

/* Project Defines */
#include "projdefines.h"

/*
 * This function starts reading a line once it detects the symbol c 
 */
bool uart_read_line_pattern(char *buffer, uint32_t max_len, const char *pattern, TickType_t timeout);

#endif  // UART_INTERFACE_H
