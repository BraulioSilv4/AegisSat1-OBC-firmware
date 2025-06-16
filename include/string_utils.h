#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"

int32_t string_to_int(char *str, uint32_t size);
char * copy_string(char * dest, const char * src, uint32_t size);
bool hexstr_to_byte(const char *hexstr, uint8_t *byte);
uint32_t string_length(const char *str);
char * find_first_char(const char *str, const char c);
char *strtok_single_char(char *str, const char delim);

#endif // STRING_UTILS_H
