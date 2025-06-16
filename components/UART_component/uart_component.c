#include "uart_component.h"

static bool uart_read_byte(uint8_t *byte) {
    return dequeue(&uartRx, byte);
}

bool uart_read_line_pattern(char *buffer, uint32_t max_len, const char *pattern, TickType_t timeout) {
    uint32_t index = 0;
    uint8_t byte;
    bool in_sentence = false;
    uint32_t pattern_len = string_length(pattern);
    uint32_t match_index = 0;
    
    TickType_t start = xTaskGetTickCount();
    TickType_t remaining = timeout;
    TickType_t elapsed;
    while (1) {
        if (xSemaphoreTake(xUartByteReady, remaining) == pdTRUE) {
            elapsed = (xTaskGetTickCount() - start);
            remaining = (elapsed < timeout) ? (timeout - elapsed) : 0;
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
        } else {
            // clear buffer
            return false;
        }
    }
}
