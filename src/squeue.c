// Source for statically allocated QUEUE

#include "squeue.h"

int SQueue_Init(uint8_t* queue, void* buffer , uint8_t element_size, uint8_t element_count)
{
	if(queue == 0 || buffer == 0 || element_size == 0 || element_count == 0)
		return SQUEUE_ERR_INIT;
	
	return 0;
}

int SQueue_Put(uint8_t* queue, void* element)
{
    return 0;
}
