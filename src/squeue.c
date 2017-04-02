// Source for statically allocated QUEUE

#include "squeue.h"
#include <string.h>

int SQueue_Init(sQueue_t* queue, void* buffer , uint8_t element_size, uint16_t element_count)
{
	if(queue == 0 || buffer == 0 || element_size == 0 || element_count == 0)
		return SQUEUE_ERR_INVALID_PAR;
	
    queue->head = (uint8_t *) buffer;
    queue->tail = (uint8_t *) buffer;
    queue->base = (uint8_t *) buffer;
    queue->element_size = element_size;
    queue->elements     = element_count;
    queue->available    = element_count;
    
	return 0;
}

int SQueue_Put(sQueue_t* queue, void* element)
{
    if(queue == 0 || element == 0)
        return SQUEUE_ERR_INVALID_PAR;
    
    if(queue->available == 0) 
        return SQUEUE_OVERFLOW;
     
    memcpy(queue->head, element, queue->element_size);   
     
    uint8_t* new_head = queue->head + queue->element_size;
    
    if(new_head == (queue->elements-1) + queue->base)
        new_head = queue->base;
    
    queue->head = new_head;
   
    if(queue->available > 0) 
        queue->available--;
  
    return 0;
}

int SQueue_Get(sQueue_t* queue, void* element)
{
    if(queue == 0 || element == 0)
        return SQUEUE_ERR_INVALID_PAR;
 
    memcpy(element, queue->tail, queue->element_size);
    
    uint8_t* new_tail = queue->tail + queue->element_size;
    
    if (new_tail == (queue->elements-1) + queue->base)
        new_tail = queue->base;
    
    queue->tail = new_tail;
    
    queue->available++;
       
    return 0;
}