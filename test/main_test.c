// Source for statically allocated FIFO main test

#include "unity.h"
#include "unity_fixture.h"

static void RunAllTests(void)
{
  RUN_TEST_GROUP(SQUEUE);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}