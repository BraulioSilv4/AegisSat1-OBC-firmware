#include "uart_interface.h"

bool uart_read_byte(uint8_t *byte) {
    return dequeue(&uartRx, byte);
}

bool uart_read_line(char *buffer, size_t max_len) {
    size_t index = 0;
    uint8_t byte;

    if(buffer == NULL || max_len == 0) {
        return false;
    }

    while(1) {
        if(xSemaphoreTake(xUartByteReady, portMAX_DELAY) == pdTRUE) {
            while(uart_read_byte(&byte)) {
                if(index < max_len - 1) { // Leaving space for null terminator
                    buffer[index++] = byte;
                    if(byte == '\n') {
                        buffer[index] = '\0';
                        return true;
                    }
                } else {
                    index = 0;
                    return false;
                }
            }
        }
    }
}

bool uart_read_line_pattern(char *buffer, size_t max_len, const char *pattern) {
    size_t index = 0;
    uint8_t byte;
    bool in_sentence = false;
    size_t pattern_len = string_length(pattern);
    size_t match_index = 0;

    while (1) {
        if (xSemaphoreTake(xUartByteReady, portMAX_DELAY) == pdTRUE) {
            while (uart_read_byte(&byte)) {

                if (!in_sentence) {
                    if (byte == pattern[match_index]) {
                        buffer[match_index++] = byte;

                        if(match_index == pattern_len) {
                            in_sentence = true;
                            index = pattern_len;
                        }
                    } else {
                        match_index = 0;
                    }
                } else {
                    if (index < max_len - 1) {
                        buffer[index++] = byte;

                        if (byte == '\n') {
                            buffer[index] = '\0';
                            return true;
                        }
                    } else {
                        in_sentence = false;
                        index = 0;
                        match_index = 0;
                        break;
                    }
                }
            }
            xSemaphoreGive(xUartByteReady);
        }
    }
}
