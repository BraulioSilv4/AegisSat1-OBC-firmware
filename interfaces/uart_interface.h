#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "hardware.h"

#include "string.h"

bool uart_read_byte(uint8_t *byte);
bool uart_read_line(char *buffer, size_t max_len);

/*
 * This function starts reading a line once it detects the symbol c 
*/
bool uart_read_line_pattern(char *buffer, size_t max_len, const char *pattern);

#endif  // UART_INTERFACE_H
