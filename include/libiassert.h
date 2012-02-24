#ifndef libiassert_H
#define libiassert_H

#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void (*signal_handler(int signum, void (*func)(int)))(int);


/*
 * macro for testing
 */
#define I_SUITE_INIT(suitename,...) \
		testfun suitename[] = {__VA_ARGS__};\
		memset(testsuite_name, 0, 1024);  \
		strncpy(testsuite_name, #suitename, strlen(#suitename))

#define I_TEST_INIT(x)	do { \
		if (!strncmp(__func__, "fail", 4)) return x; \
		memset(test_name, 0, 1024);  \
		strncpy(test_name, __func__, strlen(__func__));\
	} while(0)

#define I_ASSERT(x,fmt,...) do { \
		int _a = x; /* evaluate ONCE the expression */ \
		if (!_a) printf("I_ASSERT: " fmt"\n",  ##__VA_ARGS__ ); \
		assert(_a);\
	} while(0)

#define I_TEARDOWN_INIT  i_teardown_init()

/* a void function pointer */
typedef void (*testfun) (void);

void i_run_testsuite(testfun testsuite[], testfun setup, testfun teardown);
void i_teardown_init();

/* current testsuite name */
char testsuite_name[1024];
char test_name[1024];

extern void print_hello ();

#endif
