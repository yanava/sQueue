// Source file for sfifo test

#include "unity.h"
#include "unity_fixture.h"

#include "squeue.h"

#include <stdint.h>
#include <stdio.h>

#define BUFFER_ELEMENTS 10

TEST_GROUP(SQUEUE);

sQueue_t    queue;
uint32_t    buffer[BUFFER_ELEMENTS];
uint8_t     buffer_element_size;
uint8_t     buffer_elements;
uint32_t    element;

TEST_GROUP_RUNNER(SQUEUE)
{
  RUN_TEST_CASE(SQUEUE, InitReturnsNoErrorsWithSaneParameters );
  RUN_TEST_CASE(SQUEUE, InitReturnsErrorWithInvalidParameters );
  RUN_TEST_CASE(SQUEUE, PutReturnsNoErrorsWithSaneParameters  );
  RUN_TEST_CASE(SQUEUE, InitSetTheParametersCorrectly         );
  RUN_TEST_CASE(SQUEUE, PutReturnsErrorWithInvalidParameters  );
  RUN_TEST_CASE(SQUEUE, PutThenGetElementBack);
  RUN_TEST_CASE(SQUEUE, PutTwoAndGetTwoElementsBack);
  RUN_TEST_CASE(SQUEUE, HeadAndTailWrapAround);
  RUN_TEST_CASE(SQUEUE, ReturnsOverflowWhenQueueIsFull);
  RUN_TEST_CASE(SQUEUE, ReturnsUnderflowWhenQueueIsEmpty);
  RUN_TEST_CASE(SQUEUE, DeInitClearsAllValues);
  RUN_TEST_CASE(SQUEUE, DeInitReturnErrorWithNullQueue);
  RUN_TEST_CASE(SQUEUE, ReturnAvailableSpace);
  RUN_TEST_CASE(SQUEUE, AvailableSpaceWrapAround);
}

TEST_SETUP(SQUEUE)
{
    element = 5;
    buffer_element_size = sizeof(uint32_t);
    buffer_elements = sizeof(buffer) / buffer_element_size;
    
    SQueue_Init(&queue ,buffer,buffer_element_size,buffer_elements);
}

TEST_TEAR_DOWN(SQUEUE)
{
    element = 0;
    buffer_element_size = 0xFF;
    buffer_elements = 0xFF;   
    
    SQueue_DeInit(&queue);    
}

TEST(SQUEUE, InitReturnsNoErrorsWithSaneParameters)
{		
	TEST_ASSERT_EQUAL(0,SQueue_Init(&queue,buffer,buffer_element_size,buffer_elements));
}

TEST(SQUEUE, InitReturnsErrorWithInvalidParameters)
{    
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INVALID_PAR,SQueue_Init(0     ,buffer,buffer_element_size,buffer_elements));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INVALID_PAR,SQueue_Init(&queue,0     ,buffer_element_size,buffer_elements));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INVALID_PAR,SQueue_Init(&queue,buffer,0                  ,buffer_elements));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INVALID_PAR,SQueue_Init(&queue,buffer,buffer_element_size,0              ));    
}

TEST(SQUEUE, InitSetTheParametersCorrectly)
{
    TEST_ASSERT_EQUAL_PTR   (buffer             , queue.head         );
    TEST_ASSERT_EQUAL_PTR   (buffer             , queue.tail         );
    TEST_ASSERT_EQUAL_PTR   (buffer             , queue.base         );
    TEST_ASSERT_EQUAL_UINT8 (buffer_element_size, queue.element_size );
    TEST_ASSERT_EQUAL_UINT16(buffer_elements    , queue.elements     );
}

TEST(SQUEUE, PutReturnsNoErrorsWithSaneParameters)
{    
    TEST_ASSERT_EQUAL(0,SQueue_Put(&queue, (void *) &element));
}

TEST(SQUEUE, PutReturnsErrorWithInvalidParameters)
{    
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INVALID_PAR,SQueue_Put(0     , (void *) &element));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INVALID_PAR,SQueue_Put(&queue, 0                ));    
}

TEST(SQUEUE, PutThenGetElementBack)
{
    uint32_t recovered = 0;
    SQueue_Put(&queue, (void *) &element);
    SQueue_Get(&queue, (void *) &recovered);
    
    TEST_ASSERT_EQUAL_UINT8 (element, recovered);
}

TEST(SQUEUE, PutTwoAndGetTwoElementsBack)
{
    uint32_t recovered = 0;
    SQueue_Put(&queue, (void *) &element);
    SQueue_Get(&queue, (void *) &recovered);
    
    TEST_ASSERT_EQUAL_UINT8 (element, recovered);
    
    element = 4;
    
    recovered = 0;
    SQueue_Put(&queue, (void *) &element);
    SQueue_Get(&queue, (void *) &recovered);
    
    TEST_ASSERT_EQUAL_UINT8 (element, recovered);
}

TEST(SQUEUE, HeadAndTailWrapAround)
{
    int i = 0;
    
    uint32_t recovered = 0;
    
    for(i = 0; i < BUFFER_ELEMENTS; i++)
    {   
        SQueue_Put(&queue, (void *) &element);
        SQueue_Get(&queue, (void *) &recovered);
    }
     
    TEST_ASSERT_EQUAL_PTR (buffer, queue.head);   
    TEST_ASSERT_EQUAL_PTR (buffer, queue.tail);
}

TEST(SQUEUE, ReturnsOverflowWhenQueueIsFull)
{
    int i = 0;
    
    for(i = 0; i < BUFFER_ELEMENTS; i++)
       SQueue_Put(&queue, (void *) &element);
      
    TEST_ASSERT_EQUAL(SQUEUE_OVERFLOW, SQueue_Put(&queue, (void *) &element));
}

TEST(SQUEUE, ReturnsUnderflowWhenQueueIsEmpty)
{
    uint32_t recovered = 0xABCD;
       
    TEST_ASSERT_EQUAL(SQUEUE_UNDERFLOW, SQueue_Get(&queue, (void *) &recovered));
    TEST_ASSERT_EQUAL_UINT16(0xABCD, recovered);    
}

TEST(SQUEUE, DeInitClearsAllValues)
{
    SQueue_DeInit(&queue);
    
    TEST_ASSERT_EQUAL_PTR   (0, queue.head         );
    TEST_ASSERT_EQUAL_PTR   (0, queue.tail         );
    TEST_ASSERT_EQUAL_PTR   (0, queue.base         );
    TEST_ASSERT_EQUAL_UINT8 (0, queue.element_size );
    TEST_ASSERT_EQUAL_UINT16(0, queue.elements     );
}

TEST(SQUEUE, DeInitReturnErrorWithNullQueue)
{
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INVALID_PAR,SQueue_DeInit(0));
}

TEST(SQUEUE, ReturnAvailableSpace)
{ 
    int i = 0;

    // Queue Filling
    for (i = 0; i < (BUFFER_ELEMENTS - 1); i++)
    {
        TEST_ASSERT_EQUAL_UINT16(BUFFER_ELEMENTS-(1+i), SQueue_AvailableSpace(&queue));
        SQueue_Put(&queue, (void *) &element);
    }
}

TEST(SQUEUE, AvailableSpaceWrapAround)
{
    uint32_t recovered = 0;

    int i = 0;

    for (i = 0; i < 2*BUFFER_ELEMENTS; i++)
    {
        SQueue_Put(&queue, (void *) &element);
        SQueue_Get(&queue, (void *) &recovered);

        TEST_ASSERT_EQUAL_UINT16(BUFFER_ELEMENTS-1, SQueue_AvailableSpace(&queue));
    }
}