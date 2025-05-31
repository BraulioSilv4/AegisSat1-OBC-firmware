#include "string_utils.h"

char *copy_string(char *dest, const char *src, size_t size) {
    size_t i;
    for(i = 0; i < size && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }

    for(; i < size; i++) {
        dest[i] = '\0';
    }
    return dest;
}

bool hexstr_to_byte(const char *hexstr, uint8_t *byte) {
    if(!hexstr || !byte) return false;

    uint8_t result = 0;
    const char *p = hexstr;
    
    uint8_t i;
    for (i = 0; i < 2; i++) {  
        char c = p[i];
        uint8_t value;

        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            value = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10;
        } else {
            return false;
        }

        result = (result << 4) | value;
    }

    *byte = result;
    return true;
}

size_t string_length(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int compare_string(const char *cmp1, const char *cmp2, size_t num) {
    size_t i;
    for(i = 0; i < num; i++) {
        if(cmp1[i] != cmp2[i] || cmp1[i] == '\0' || cmp2[i] == '\0') {
            return 1;
        }
    }

    return 0;
}

char *find_first_char(const char *str, const char c) {
    while(*str) {
        if(*str == c) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}

char *strtok_single_char(char *str, const char delim) {
    static char *next = NULL;
    if(str != NULL) {
        next = str;
    }

    if(next == NULL) {
        return NULL;
    } 

    while(*next == delim) {
        next++;
    }

    if(*next == '\0') {
        next = NULL;
        return NULL;
    }

    char *token_start = next;
    while(*next && *next != delim) {
        next++;
    }

    if(*next == delim) {
        *next = '\0';
        next++;
    } else {
        next = NULL;
    }

    return token_start;
}
