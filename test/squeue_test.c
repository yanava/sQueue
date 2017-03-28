// Source file for sfifo test

#include "unity.h"
#include "unity_fixture.h"

#include "squeue.h"

#include <stdint.h>

TEST_GROUP(SQUEUE);

uint8_t *queue;

TEST_GROUP_RUNNER(SQUEUE)
{
  RUN_TEST_CASE(SQUEUE, SQueue_InitReturnsNoErrorsWithSaneParameters );
  RUN_TEST_CASE(SQUEUE, SQueue_InitReturnsErrorWithInvalidParameters );
  RUN_TEST_CASE(SQUEUE, SQueue_PutReturnsNoErrorsWithSaneParameters  );
}

TEST_SETUP(SQUEUE)
{
    queue = malloc(1);
}

TEST_TEAR_DOWN(SQUEUE)
{
    free(queue);
}

TEST(SQUEUE, SQueue_InitReturnsNoErrorsWithSaneParameters)
{		
	uint8_t  buffer[5];
	uint8_t  buffer_element_size = sizeof(uint8_t);
	uint8_t  buffer_elements = sizeof(buffer) / buffer_element_size;
	
	TEST_ASSERT_EQUAL(0,SQueue_Init(queue,buffer,buffer_element_size,buffer_elements));
}

TEST(SQUEUE, SQueue_InitReturnsErrorWithInvalidParameters)
{
    uint8_t  buffer[5];
	uint8_t  buffer_element_size = sizeof(uint8_t);
	uint8_t  buffer_elements = sizeof(buffer) / buffer_element_size; 
    
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INIT,SQueue_Init(0    ,buffer,buffer_element_size,buffer_elements));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INIT,SQueue_Init(queue,0     ,buffer_element_size,buffer_elements));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INIT,SQueue_Init(queue,buffer,0                  ,buffer_elements));
    TEST_ASSERT_EQUAL(SQUEUE_ERR_INIT,SQueue_Init(queue,buffer,buffer_element_size,0              ));    
}

TEST(SQUEUE, SQueue_PutReturnsNoErrorsWithSaneParameters)
{
    uint8_t element = 5;
    
    TEST_ASSERT_EQUAL(0,SQueue_Put(queue, (void *) &element));
}
