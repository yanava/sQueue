// Source for statically allocated QUEUE

#ifndef __SQUEUE_H_
#define __SQUEUE_H_

#include <stdint.h>

#define SQUEUE_ERROR_MIN (-10)

enum SQUEUE_ERRORS
{
    SQUEUE_ERR_INIT,
};

int SQueue_Init(uint8_t* queue, void* buffer, uint8_t element_size, uint8_t element_count);
int SQueue_Put(uint8_t* queue, void* element);

#endif  // __SFIFO_H_