#include "libiassert.h"

void
print_hello(){
  printf("MySQL Embeddet Tutorial\n");
}

/**
 * Remove any teardown handler in teardown functions.
 *
 * TODO ensure in some way that the handler is set to default
 */
void i_teardown_init() {
	signal_handler(SIGABRT, SIG_DFL);
}

/**
 * Associate a signal on setup. Still unused
 */
void i_setup(testfun f) {
	if (f)
		signal_handler(SIGUSR1, (void (*)(int)) f);
}

/**
 * On SIGABRT run teardown function
 */
void i_teardown(testfun f) {
	if (f) {
		signal_handler(SIGUSR2, (void (*)(int)) f);
		signal_handler(SIGABRT, (void (*)(int)) f);
	}
}

/**
 * Run a testsuite, which is a NULL terminated list of functions:
 * ex. testfun testsuite [] = {method_one, method_two, NULL};
 *
 * you may override setup and teardown
 */
void i_run_testsuite(testfun testsuite[], testfun setup, testfun teardown) {
	// cursor pointer to current method
	testfun *fp = NULL;

	int test_no=0;
	// run all tests
	for (fp=testsuite; *fp!=NULL; fp++, test_no++) {
		fprintf(stderr, "test id: %d\n", test_no);

		// reset signal handler for setup/teardown
		// because method may override signal handlers
		i_teardown(teardown);
		i_setup(setup);

		// run setup and teardown
		//kill(getpid(), SIGUSR1);
		if (setup)
			setup();
		//
		// run method
		//
		(*fp)();

		fprintf(stderr, "test %s ok\n", test_name);
		// teardown
		if (teardown)
			teardown();
	}
	fprintf(stderr, "testsuite %s ok\n", testsuite_name);
}
