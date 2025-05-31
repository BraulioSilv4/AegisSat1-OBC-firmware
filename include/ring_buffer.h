#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include "projdefines.h"
#include "stdint.h"
#include "stdbool.h"

typedef struct {
    char buffer[RING_BUF_MAX_SIZE];
    volatile int8_t head;
    volatile int8_t tail;
} RingBuffer;

inline bool is_full(RingBuffer* buf) {
    int8_t next_head = buf->head + 1;
    if (next_head >= RING_BUF_MAX_SIZE) next_head = 0;
    return buf->tail == next_head;
}

inline bool is_empty(RingBuffer* buf) {
    return buf->head == -1;
}

inline bool enqueue(RingBuffer* buf, char data) {
    if(is_full(buf)) {
        return -1;
    }

    if(buf->tail == -1) {
        buf->tail = 0;
    }

    if(++buf->head >= RING_BUF_MAX_SIZE) {buf->head = 0;}
    buf->buffer[buf->head] = data;
    return 1;
}

inline bool dequeue(RingBuffer* buf, uint8_t * byte) {
    if(is_empty(buf)) {
        return false;
    }

    uint8_t data = buf->buffer[buf->tail];

    if(buf->tail == buf->head) {
        buf->head = -1;
        buf->tail = -1;
    } else {
        if(++buf->tail >= RING_BUF_MAX_SIZE) {buf->tail = 0;};
    }
    
    *byte = data; 
    return true;
}


#endif  // RING_BUFFER_H
