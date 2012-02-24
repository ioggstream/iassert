/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Roberto Polli
 Version     :
 Copyright   : LGPLv3
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libiassert/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */
#include <errno.h>
#include <unistd.h>
#include "libiassert.h"

// global variables
char *test_one_string=NULL;

/**
 * prototypes
 */
void setup();
void teardown();

/**
 * tests
 */
void my_first_test();
void test_one();


/**
 * My first test function, that doesn't require setup and teardown.
 */
void my_first_test() {
	I_TEST_INIT();

	I_ASSERT(puts("I_ASSERT is simple")>0 , "error using puts()");
}

/**
 * A setup test_one_string which allocates a test_one_string
 */
void setup() {
	printf("this is a setup method");
	test_one_string = malloc(1024);
	I_ASSERT(test_one_string != NULL, "error in malloc(): %d", errno);
}

/**
 * declare a teardown method using the I_TEARDOWN_INIT macro
 */
void teardown() {
	I_TEARDOWN_INIT;

	// free allocated memory, so that
	// valgrind won't complain ;)
	free(test_one_string);
	test_one_string = NULL;
}

/**
 * declare a test case with the I_TEST_INIT macro
 */
void test_one() {
	I_TEST_INIT();

	// test will nicely fail if test_one_string is null, printing the given message
	// and the failing line.
	// After failure, the teardown method is executed
	I_ASSERT(test_one_string != NULL, "cannot allocate test_one_string");

	printf("sting address is %p\n", test_one_string);
	sprintf(test_one_string,"I_ASSERT is cool on %d" , getpid());

	printf("String content is [%s]\n", test_one_string);
}
/**
 * if a test is still in failure state and need some work, you can skip it
 * prepending "fail" to the test name.
 * NOTE setup and teardown are STILL executed
 */
void fail_test_two() {
	I_TEST_INIT();

	// test will nicely fail if test_one_string is null, printing the given message
	// and the failing line.
	// After failure, the teardown method is executed
	I_ASSERT(test_one_string != NULL, "cannot allocate test_one_string");

	printf("sting address is %p\n", test_one_string);
	sprintf(test_one_string,"I_ASSERT is cool on %d" , getpid());

	printf("String content is [%s]\n", test_one_string);
}



int main(void) {

	//
	// my first, trivial, testsuite
	//
	I_SUITE_INIT(testsuite_zero,
			my_first_test
	);
	i_run_testsuite(testsuite_zero, NULL, NULL);


	// another testsuite with setup and teardown
	I_SUITE_INIT( testsuite_one,
			test_one,
			fail_test_two
	);
	i_run_testsuite(testsuite_one, setup, teardown);


	I_SUITE_INIT(testsuite_two,
			my_first_test,
			test_one,
			fail_test_two,
			NULL);
	i_run_testsuite(testsuite_two, setup, teardown);


	_exit(0);
}
