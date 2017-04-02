// Source file for sfifo test

#include "unity.h"
#include "unity_fixture.h"

#include "squeue.h"

#include <stdint.h>
#include <stdio.h>

#define BUFFER_ELEMENTS 5

TEST_GROUP(SQUEUE);

sQueue_t    queue;
uint32_t    buffer[BUFFER_ELEMENTS];
uint8_t     buffer_element_size;
uint8_t     buffer_elements;
uint32_t    element;

TEST_GROUP_RUNNER(SQUEUE)
{
  RUN_TEST_CASE(SQUEUE, SQueue_InitReturnsNoErrorsWithSaneParameters );
  RUN_TEST_CASE(SQUEUE, SQueue_InitReturnsErrorWithInvalidParameters );
  RUN_TEST_CASE(SQUEUE, SQueue_PutReturnsNoErrorsWithSaneParameters  );
  RUN_TEST_CASE(SQUEUE, SQueue_InitSetTheParametersCorrectly         );
  RUN_TEST_CASE(SQUEUE, SQueue_PutReturnsErrorWithInvalidParameters  );
  RUN_TEST_CASE(SQUEUE, SQueue_PutThenGetElementBack);
  RUN_TEST_CASE(SQUEUE, SQueue_PutTwoAndGetTwoElementsBack);
  RUN_TEST_CASE(SQUEUE, SQueue_HeadWrapsAround);
  RUN_TEST_CASE(SQUEUE, SQueue_TailWrapsAround);
}

TEST_SETUP(SQUEUE)
{
    element = 5;
    buffer_element_size = sizeof(uint32_t);
    buffer_elements = sizeof(buffer) / buffer_element_size;
}

TEST_TEAR_DOWN(SQUEUE)
{
    element = 0;
    buffer_element_size = 0xFF;
    buffer_elements = 0xFF;
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
    SQueue_Init(&queue ,buffer,buffer_element_size,buffer_elements);
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

TEST(SQUEUE, SQueue_PutThenGetElementBack)
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

TEST(SQUEUE, HeadWrapsAround)
{
    int i = 0;
    
    for(i = 0; i < BUFFER_ELEMENTS; i++)
       SQueue_Put(&queue, (void *) &element);

    TEST_ASSERT_EQUAL_PTR (buffer, queue.head);
}

TEST(SQUEUE, TailWrapsAround)
{
    int i = 0;
    
    uint32_t recovered = 0;
    
    for(i = 0; i < BUFFER_ELEMENTS; i++)
    {
        SQueue_Put(&queue, (void *) &element);
        SQueue_Get(&queue, (void *) &recovered);
    }
       

    TEST_ASSERT_EQUAL_PTR (buffer, queue.tail);
}

TEST(SQUEUE, ReturnsOverflowWhenQueueIsFull)
{
    
}

