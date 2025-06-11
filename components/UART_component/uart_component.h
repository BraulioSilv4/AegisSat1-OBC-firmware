#ifndef UART_COMPONENT_H
#define UART_COMPONENT_H

#include "UART_driver/uart.h"
#include "string_utils.h"

#include "stdint.h"
#include "stdbool.h"

/*
 * This function reads a until a new line is found
 */
bool uart_read_line(char *buffer, size_t max_len);

/*
 * This function starts reading a line once it detects the symbol c 
 */
bool uart_read_line_pattern(char *buffer, size_t max_len, const char *pattern);

#endif  // UART_INTERFACE_H
