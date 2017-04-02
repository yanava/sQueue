// Source for statically allocated QUEUE

#ifndef __SQUEUE_H_
#define __SQUEUE_H_

#include <stdint.h>

#define SQUEUE_ERROR_MIN (-10)

enum SQUEUE_ERRORS
{
    SQUEUE_ERR_INVALID_PAR = SQUEUE_ERROR_MIN,
    SQUEUE_OVERFLOW,
};

typedef struct sQueue_tag
{
    uint8_t*  head;
    uint8_t*  tail;
    uint8_t*  base;
    int32_t   available;
    uint16_t  elements;
    uint8_t   element_size;
} sQueue_t;

int SQueue_Init(sQueue_t* queue, void* buffer, uint8_t element_size, uint16_t element_count);
int SQueue_Put(sQueue_t* queue, void* element);
int SQueue_Get(sQueue_t* queue, void* element);


#endif  // __SFIFO_H_