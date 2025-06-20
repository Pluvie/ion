/**
 * Test framework.
 *
 * Example:
 * ```c
 * test(malloc, example) {                                // wrap the test with `test()`
 *                                                        //
 *   given("a pointer");                                  // set the subject with
 *     void* pointer;                                     // `given()`
 *                                                        //
 *   when("it is initialized to NULL");                   // conditions can be expressed
 *     pointer = NULL;                                    // with `when()`
 *                                                        //
 *   calling("malloc()");                                 // the function to be tested
 *     pointer = malloc(32);                              // is defined with `calling()`
 *                                                        //
 *   must("assign a memory address to the pointer");      // the end result can be
 *     verify(pointer != NULL);                           // enforced with `must()`
 *                                                        //
 *   success();                                           // closing operations can be
 *     free(pointer);                                     // done after `success()`
 * }                                                      //
 * ```
 *
 * This (very) simple framework should give you the basic tools to write test functions
 * in a natural and readable fashion. */


/**
 * Global variable that stores original pointer to the stderr stream. */
FILE* original_stderr;


/**
 * Global variable that stores the main program pid for forked tests. */
int tests_pid;


/**
 * Global variable that store the forked program pid for forked tests. */
int tests_forked_pid;


/**
 * Global variable that allows automatic allocation and deallocation of objects in
 * a test case. */
memory* test_allocator;


/**
 * Global variable that stores the final result of all test. */
bool tests_passed = true;


/**
 * Global variable that stores registered tests to be run. */
int registered_tests_count = 0;
void (*registered_tests[8192])(void) = { 0 };
char* registered_test_names[8192] = { 0 };


/**
 * Global variable that stores focused tests to be run. */
int focused_tests_count = 0;
void (*focused_tests[16])(void) = { 0 };
char* focused_test_names[16] = { 0 };


/**
 * Returns a test case function name. */
#define test_function(test_function, test_case)                                         \
  test_function ## __ ## test_case


/**
 * Defines a test case. */
#define test(test_function, test_case)                                                  \
  void test_function ## __ ## test_case(void)


/**
 * Registers a test case. */
#define test_add(test_function, test_case)                                              \
  registered_tests[registered_tests_count] = test_function ## __ ## test_case;          \
  registered_test_names[registered_tests_count] = "  " #test_function " | " #test_case; \
  registered_tests_count++;


/**
 * Focuses a test case. */
#define test_focus(test_function, test_case)                                            \
  focused_tests[focused_tests_count] = test_function ## __ ## test_case;                \
  focused_test_names[focused_tests_count] = "  " #test_function " | " #test_case;       \
  focused_tests_count++;


/**
 * Forks a test. Example usage:
 * ```c
 * test( fork, example ) {
 * 
 *   given("a main process");
 *     int pid = getpid();
 * 
 * 
 *   when("a forked process starts");
 *     test_fork() {
 *       signal_catch(SIGINT);
 *       sleep(10);
 *       exit(0);
 *     }
 *     verify(pid != tests_forked_pid);
 *     sleep(1);
 * 
 * 
 *   calling("kill()");
 *     kill(tests_forked_pid, SIGINT);
 * 
 * 
 *   must("terminate the forked process");
 * 
 * 
 *   success();
 *     test_wait_forked();
 * }
 * ``` */
#define test_fork()                                                                     \
  if ((tests_forked_pid = fork()) == 0)


/**
 * Waits a forked test. */
#define test_wait_forked()                                                              \
  int lvar(wait_status); wait(&lvar(wait_status));


#define given(description)
#define when(description)
#define calling(description)
#define must(description)


/**
 * Verifies a condition. */
#define verify(condition)                                                               \
  if (!(condition)) { test_failed(__FILE__, __LINE__, #condition ); }


/**
 * Checks the error message. */
#define error_is(expected_message)                                                      \
  (strncmp(error.message, expected_message, error.length) == 0)


/**
 * The test is successful. */
#define success()                                                                       \
  fprintf(original_stderr, "\r");                                                       \
  fprintf(original_stderr, PRINT_COLOR_GREEN);                                          \
  fprintf(original_stderr, "█ ");                                                       \
  fprintf(original_stderr, PRINT_COLOR_NONE);                                           \
  fprintf(original_stderr, "\n");                                                       \
end_test:


/**
 * The test has failed. */
#define test_failed(location_name, line_num, message)                                   \
  fprintf(original_stderr, "\r");                                                       \
  fprintf(original_stderr, PRINT_COLOR_RED);                                            \
  fprintf(original_stderr, "█ ");                                                       \
  fprintf(original_stderr, PRINT_COLOR_NONE);                                           \
  fprintf(original_stderr, "\n");                                                       \
  fprintf(original_stderr, PRINT_COLOR_RED);                                            \
  fprintf(original_stderr, "  %s (%s:%i)", message, location_name, line_num);           \
  fprintf(original_stderr, PRINT_COLOR_NONE);                                           \
  fprintf(original_stderr, "\n");                                                       \
  tests_passed = false;                                                                 \
  goto end_test;


/**
 * Runs the registered tests. */
void tests_run (
    void
)
{
  tests_pid = getpid();
  test_allocator = calloc(1, sizeof(memory));

  if (focused_tests[0] == NULL) {
    original_stderr = fdopen(STDERR_FILENO, "w");
    stderr = fopen("/dev/null", "w");
  } else {
    original_stderr = fdopen(STDERR_FILENO, "w");
  }

  if (focused_tests[0] == NULL) {
    for (int i = 0; i < registered_tests_count; i++) {
      fprintf(original_stderr, "%s", registered_test_names[i]);
      fflush(original_stderr);
      registered_tests[i]();
      memory_release(test_allocator);
      error_reset();
    }
  } else {
    for (int i = 0; i < focused_tests_count; i++) {
      fprintf(original_stderr, "%s", focused_test_names[i]);
      fflush(original_stderr);
      focused_tests[i]();
      if (!tests_passed)
        error_print();
      memory_release(test_allocator);
      error_reset();
    }
  }

  if (tests_passed) {
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_GREEN);
    if (focused_tests[0] == NULL)
      fprintf(original_stderr, "Completed %li tests.\n", registered_tests_count);
    else
      fprintf(original_stderr, "Completed %li focused test(s).\n", focused_tests_count);
    fprintf(original_stderr, "All tests passed successfully.");
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_NONE);
  } else {
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_RED);
    fprintf(original_stderr, "Some tests did not pass. Check for errors above.");
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_NONE);
  }

  fclose(original_stderr);
  fclose(stderr);
  free(test_allocator);
}
