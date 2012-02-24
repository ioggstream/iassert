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
#include <unistd.h>
#include <string.h>
#include "libiassert.h"

// global variables
char *test_one_string=NULL;

void test_one();

void test_one() {
	I_TEST_INIT();

	I_ASSERT(test_one_string != NULL, "test_one_string is null and was not allocated");

	printf("sting address is %p\n", test_one_string);
	sprintf(test_one_string,"I_ASSERT is cool on %d" , getpid());

	printf("String content is [%s]\n", test_one_string);
}

int main(void) {

	// define once a new testsuite to
	// be run with different setup/teardown
	I_SUITE_INIT(testsuite_one,
			test_one
	);

	{	// you can use different setup and teardown methods
		// defining them directly in your testsuite
		void setup() {
			puts("setup one");
			test_one_string = malloc(1024);
		}
		void teardown() {
			I_TEARDOWN_INIT;
			free(test_one_string);
			test_one_string = NULL;
		}

		i_run_testsuite(testsuite_one, setup, teardown);
	}

	{	// run the previous testsuite with different
		// setup. this causes an assertion error
		void setup() {
			puts("setup two, no string allocation");
		}
		void teardown() {
			I_TEARDOWN_INIT;
			free(test_one_string);
			test_one_string = NULL;
		}

		i_run_testsuite(testsuite_one, setup, teardown);
	}


	return 0;
}
