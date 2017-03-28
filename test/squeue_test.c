// Source file for sfifo test

#include "unity.h"
#include "unity_fixture.h"

#include "squeue.h"

#include <stdint.h>

TEST_GROUP(SQUEUE);

sQueue_t  queue;
uint8_t   buffer[5];
uint8_t   buffer_element_size;
uint8_t   buffer_elements;

TEST_GROUP_RUNNER(SQUEUE)
{
  RUN_TEST_CASE(SQUEUE, SQueue_InitReturnsNoErrorsWithSaneParameters );
  RUN_TEST_CASE(SQUEUE, SQueue_InitReturnsErrorWithInvalidParameters );
  RUN_TEST_CASE(SQUEUE, SQueue_PutReturnsNoErrorsWithSaneParameters  );
  RUN_TEST_CASE(SQUEUE, SQueue_InitSetTheParametersCorrectly         );
}

TEST_SETUP(SQUEUE)
{
    buffer_element_size = sizeof(uint8_t);
    buffer_elements = sizeof(buffer) / buffer_element_size;
}

TEST_TEAR_DOWN(SQUEUE)
{
    buffer_element_size = 0xFF;
    buffer_elements = 0xFF;
}

TEST(SQUEUE, SQueue_InitReturnsNoErrorsWithSaneParameters)
{		
	TEST_ASSERT_EQUAL(0,SQueue_Init(&queue,buffer,buffer_element_size,buffer_elements));
}

TEST(SQUEUE, SQueue_InitReturnsErrorWithInvalidParameters)
{    
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INIT,SQueue_Init(0    ,buffer,buffer_element_size,buffer_elements));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INIT,SQueue_Init(&queue,0     ,buffer_element_size,buffer_elements));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INIT,SQueue_Init(&queue,buffer,0                  ,buffer_elements));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INIT,SQueue_Init(&queue,buffer,buffer_element_size,0              ));    
}

TEST(SQUEUE, SQueue_InitSetTheParametersCorrectly)
{
    SQueue_Init(&queue ,buffer,buffer_element_size,buffer_elements);
    TEST_ASSERT_EQUAL_PTR   (buffer             , queue.head         );
    TEST_ASSERT_EQUAL_PTR   (buffer             , queue.tail         );
    TEST_ASSERT_EQUAL_PTR   (buffer             , queue.base         );
    TEST_ASSERT_EQUAL_UINT8 (buffer_element_size, queue.element_size );
    TEST_ASSERT_EQUAL_UINT16(buffer_elements    , queue.elements     );
}


TEST(SQUEUE, SQueue_PutReturnsNoErrorsWithSaneParameters)
{
    uint8_t element = 5;
    
    TEST_ASSERT_EQUAL(0,SQueue_Put(&queue, (void *) &element));
}
