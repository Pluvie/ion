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
 * Global variable that stores the final result of all test. */
bool suite_passed = true;


/**
 * Global variable that stores registered tests to be run. */
u32 registered_tests_count = 0;
void (*registered_tests[8192])(void) = { 0 };
char* registered_test_names[8192] = { 0 };


/**
 * Global variable that stores focused tests to be run. */
u32 focused_tests_count = 0;
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
 * Enables test printing inside this macro. Normally, all printing inside tests is
 * redirected to `/dev/null`. By using this macro, the variable #suppressed_stderr shall
 * be temporarily reverted back, enabling to print on `stderr`. */
#define test_print()                                                                    \
  tmp_stderr = suppressed_stderr; suppressed_stderr = original_stderr;                  \
  i32 lvar(l) = 0; for (; lvar(l) == 0; (suppressed_stderr = tmp_stderr), (lvar(l)++))


#define given(description)
#define when(description)
#define calling(description)
#define must(description)


/**
 * Verifies a condition. */
#define verify(condition)                                                               \
  if (!(condition)) { test_failed(__FILE__, __LINE__, #condition ); }


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
  suite_passed = false;                                                                 \
  goto end_test;
