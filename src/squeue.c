// Source for statically allocated QUEUE

#include "squeue.h"
#include <string.h>
#include <stdio.h>

int SQueue_Init(sQueue_t* queue, void* buffer , uint8_t element_size, uint16_t element_count)
{
	if(queue == 0 || buffer == 0 || element_size == 0 || element_count == 0)
		return SQUEUE_ERR_INVALID_PAR;
	
    queue->head = (uint8_t *) buffer;
    queue->tail = (uint8_t *) buffer;
    queue->base = (uint8_t *) buffer;
    queue->element_size = element_size;
    queue->elements     = element_count;
    
	return 0;
}

int SQueue_DeInit(sQueue_t* queue)
{
    if(queue == 0)
        return SQUEUE_ERR_INVALID_PAR;
        
    queue->head = 0;
    queue->tail = 0;
    queue->base = 0;
    queue->element_size = 0;
    queue->elements = 0;
    return 0;
}

int SQueue_Put(sQueue_t* queue, void* element)
{
    if(queue == 0 || element == 0)
        return SQUEUE_ERR_INVALID_PAR;
     
    uint8_t* new_head = queue->head + queue->element_size;

    if(new_head == queue->elements*queue->element_size + queue->base)
        new_head = queue->base; 
    
    if(new_head == queue->tail)
        return SQUEUE_OVERFLOW;

    else
    {
        memcpy(new_head, element, queue->element_size);
        queue->head = new_head;    
    }
    
    return 0;
}

int SQueue_Get(sQueue_t* queue, void* element)
{
    if(queue == 0 || element == 0)
        return SQUEUE_ERR_INVALID_PAR;
 
    if(queue->tail == queue->head)
        return SQUEUE_UNDERFLOW;

    uint8_t* new_tail = queue->tail + queue->element_size;

    if (new_tail == queue->elements*queue->element_size + queue->base)
        new_tail = queue->base;
 
    memcpy(element, new_tail, queue->element_size);
    queue->tail = new_tail;
       
    return 0;
}

int SQueue_AvailableSpace(sQueue_t* queue)
{
    if(queue == 0)
        return SQUEUE_ERR_INVALID_PAR;

    if(queue->head == queue->tail)
        return (queue->elements - 1);
    else if (queue->head > queue->tail)
        return (queue->elements - (queue->head - queue->tail)/queue->element_size - 1);
    else
        return ((queue->tail - queue->head)/queue->element_size - 1);

}