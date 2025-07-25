#include "string_utils.h"

int32_t string_to_int(char *str, uint32_t size) {
    int32_t value = 0;
    int8_t is_negative = 1;

    uint32_t i;
    for(i = 0; i < size; i++) {
        char c = str[i];

        if(c == '-') {
            is_negative = -1;
        }

        if(c >= '0' && c <= '9') {
            value = value * 10 + (c - '0');
        }
    }

    return (value * is_negative);
}

int32_t nmea_int(char *str) {
    int32_t value = 0;
    int8_t is_negative = 1;

    uint32_t i = 0;
    while(str[i] != ',' && str[i] != '*') {
        char c = str[i];

        if(c == '-') {
            is_negative = -1;
        }

        if(c >= '0' && c <= '9') {
            value = value * 10 + (c - '0');
        }
        i++;
    }

    return (value * is_negative);
}

char *copy_string(char *dest, const char *src, uint32_t size) {
    uint32_t i;
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

uint32_t string_length(const char *str) {
    uint32_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
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

void * cpymem(void * dest, const void * src, uint32_t length) {
    uint8_t * d = (uint8_t *) dest;
    const uint8_t * s = (const uint8_t *) src;
    uint32_t i;
    for (i = length; i-- > 0; ) {
        d[i] = s[i];
    }
    return dest;
}

void * setmem(void * ptr, uint8_t value, uint32_t length) {
    uint8_t * p = (uint8_t *) ptr;
    uint32_t i;
    for (i = length; i-- > 0; ) {
        p[i] = value;
    }

    return ptr;
}
