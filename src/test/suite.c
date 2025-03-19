#include "suites/core.c"
#include "suites/array.c"
#include "suites/io.c"
#include "suites/map.c"
#include "suites/range.c"
#include "suites/string.c"
#include "suites/time.c"
#include "suites/vector.c"
#include "suites/tensor.c"
#include "suites/reflection.c"
#include "suites/binary.c"
#include "suites/csv.c"
#include "suites/json.c"
#include "suites/tcp.c"

bool suite_register (
    i32 argc,
    char** argv
)
{
  if (argc == 2)
    goto run_specific_suite;

  test_suite__core();
  test_suite__array();
  test_suite__io();
  test_suite__map();
  test_suite__range();
  test_suite__string();
  test_suite__time();
  test_suite__vector();
  test_suite__tensor();
  test_suite__reflection();
  test_suite__binary();
  test_suite__csv();
  test_suite__json();
  test_suite__tcp();

  return true;

run_specific_suite:
  char* module = argv[1];

        if (strcmp(module, "core") == 0)
    test_suite__core();
  else  if (strcmp(module, "array") == 0)
    test_suite__array();
  else  if (strcmp(module, "io") == 0)
    test_suite__io();
  else  if (strcmp(module, "map") == 0)
    test_suite__map();
  else  if (strcmp(module, "range") == 0)
    test_suite__range();
  else  if (strcmp(module, "string") == 0)
    test_suite__string();
  else  if (strcmp(module, "time") == 0)
    test_suite__time();
  else  if (strcmp(module, "vector") == 0)
    test_suite__vector();
  else  if (strcmp(module, "tensor") == 0)
    test_suite__tensor();
  else  if (strcmp(module, "reflection") == 0)
    test_suite__reflection();
  else  if (strcmp(module, "binary") == 0)
    test_suite__binary();
  else  if (strcmp(module, "csv") == 0)
    test_suite__csv();
  else  if (strcmp(module, "json") == 0)
    test_suite__json();
  else  if (strcmp(module, "tcp") == 0)
    test_suite__tcp();
  else
    goto unrecognized_module;

  return true;

unrecognized_module:
  fprintf(original_stderr, "\n");
  fprintf(original_stderr, PRINT_COLOR_RED);
  fprintf(original_stderr, "Unrecognized module: `%s`.", module);
  fprintf(original_stderr, "\n");
  fprintf(original_stderr, PRINT_COLOR_NONE);

  return false;
}


void suite_run (
    void
)
{
  if (focused_tests[0] == NULL) {
    original_stderr = fdopen(STDERR_FILENO, "w");
    stderr = fopen("/dev/null", "w");
  } else {
    original_stderr = fdopen(STDERR_FILENO, "w");
    stderr = fdopen(STDERR_FILENO, "w");
  }

  if (focused_tests[0] == NULL) {
    for (u32 i = 0; i < registered_tests_count; i++) {
      fprintf(original_stderr, "%s", registered_test_names[i]);
      registered_tests[i]();
      error_reset();
    }
  } else {
    for (u32 i = 0; i < focused_tests_count; i++) {
      fprintf(original_stderr, "%s", focused_test_names[i]);
      focused_tests[i]();
      if (!suite_passed)
        error_print();
      error_reset();
    }
  }

  if (suite_passed) {
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_GREEN);
    if (focused_tests[0] == NULL)
      fprintf(original_stderr, "Completed %i tests.\n", registered_tests_count);
    else
      fprintf(original_stderr, "Completed %i focused test(s).\n", focused_tests_count);
    fprintf(original_stderr, "The test suite passed successfully.");
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_NONE);
  } else {
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_RED);
    fprintf(original_stderr, "The test suite did not pass. Check for errors above.");
    fprintf(original_stderr, "\n");
    fprintf(original_stderr, PRINT_COLOR_NONE);
  }

  fclose(original_stderr);
  fclose(stderr);
}
