#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"

char * copy_string(char * dest, const char * src, size_t size);
bool hexstr_to_byte(const char *hexstr, uint8_t *byte);
size_t string_length(const char *str);
int compare_string(const char *cmp1, const char *cmp2, size_t num);
char * find_first_char(const char *str, const char c);
char *strtok_single_char(char *str, const char delim);

#endif // STRING_UTILS_H
