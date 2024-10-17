/**
 * Defines a focused test case. */
#ifdef FOCUSED_SUITE

#define focus_test(test_function, test_case)                                            \
  char* test_case_in_focus = #test_function " | " #test_case;                           \
  void test_function ## __ ## test_case(void)

#else

char* test_case_in_focus = NULL;

#define focus_test(test_function, test_case)                                            \
  void test_function ## __ ## test_case(void)

#endif




/**
 * Redefines the macro to run a focused test case.
 *
 * This macro overrides ⚡️ION⚡️ `test_run` macro to introduce a check if there is a
 * focused test: if present, only the focused test shall be run.
 *
 * Also, if there is a focused test, enables full printing on stderr, in order to
 * ease the debugging. */
#undef test_run
#define test_run(test_function, test_case)                                              \
  if (test_case_in_focus == NULL ||                                                     \
      streq(#test_function " | " #test_case, test_case_in_focus)) {                     \
                                                                                        \
    fprintf(original_stderr, "  " #test_function " | " #test_case);                     \
                                                                                        \
    error_reset();                                                                      \
                                                                                        \
    if (test_case_in_focus != NULL &&                                                   \
        streq(#test_function " | " #test_case, test_case_in_focus)) {                   \
      tmp_stderr = suppressed_stderr;                                                   \
      suppressed_stderr = original_stderr;                                              \
    }                                                                                   \
                                                                                        \
    test_function ## __ ## test_case();                                                 \
                                                                                        \
    if (test_case_in_focus != NULL &&                                                   \
        streq(#test_function " | " #test_case, test_case_in_focus)) {                   \
      suppressed_stderr = tmp_stderr;                                                   \
    }                                                                                   \
  }
