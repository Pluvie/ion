#include "suites/core.c"

#include "suites/array.c"
#include "suites/date.c"
#include "suites/io.c"
#include "suites/map.c"
#include "suites/vector.c"

#include "suites/string.c"
#include "suites/reflection.c"

#include "suites/binary.c"
#include "suites/json.c"

bool suite_register (
    i32 argc,
    char** argv
)
{
  if (argc == 2)
    goto run_specific_suite;

  test_suite__core();
  test_suite__array();
  test_suite__date();
  test_suite__io();
  test_suite__map();
  test_suite__vector();
  test_suite__string();
  test_suite__reflection();
  test_suite__binary();
  test_suite__json();

  return true;

run_specific_suite:
  char* module = argv[1];

        if (strcmp(module, "core") == 0)
    test_suite__core();
  else  if (strcmp(module, "array") == 0)
    test_suite__array();
  else  if (strcmp(module, "date") == 0)
    test_suite__date();
  else  if (strcmp(module, "io") == 0)
    test_suite__io();
  else  if (strcmp(module, "map") == 0)
    test_suite__map();
  else  if (strcmp(module, "vector") == 0)
    test_suite__vector();
  else  if (strcmp(module, "string") == 0)
    test_suite__string();
  else  if (strcmp(module, "reflection") == 0)
    test_suite__reflection();
  else  if (strcmp(module, "binary") == 0)
    test_suite__binary();
  else  if (strcmp(module, "json") == 0)
    test_suite__json();
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
