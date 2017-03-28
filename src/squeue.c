// Source for statically allocated QUEUE

#include "squeue.h"

int SQueue_Init(sQueue_t* queue, void* buffer , uint8_t element_size, uint16_t element_count)
{
	if(queue == 0 || buffer == 0 || element_size == 0 || element_count == 0)
		return SQUEUE_ERR_INIT;
	
    queue->head = (uint8_t *) buffer;
    queue->tail = (uint8_t *) buffer;
    queue->base = (uint8_t *) buffer;
    queue->element_size = element_size;
    queue->elements     = element_count;
    
	return 0;
}

int SQueue_Put(sQueue_t* queue, void* element)
{
    return 0;
}
