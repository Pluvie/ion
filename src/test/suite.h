i32 suite_pid;
i32 forked_pid;
memory* test_allocator;

void suite_run (
    void
)
{
  suite_pid = getpid();
  test_allocator = calloc(1, sizeof(memory));

  if (focused_tests[0] == NULL) {
    original_stderr = fdopen(STDERR_FILENO, "w");
    stderr = fopen("/dev/null", "w");
  } else {
    original_stderr = fdopen(STDERR_FILENO, "w");
  }

  if (focused_tests[0] == NULL) {
    for (u32 i = 0; i < registered_tests_count; i++) {
      fprintf(original_stderr, "%s", registered_test_names[i]);
      fflush(original_stderr);
      registered_tests[i]();
      memory_release(test_allocator);
      error_reset();
    }
  } else {
    for (u32 i = 0; i < focused_tests_count; i++) {
      fprintf(original_stderr, "%s", focused_test_names[i]);
      fflush(original_stderr);
      focused_tests[i]();
      if (!suite_passed)
        error_print();
      memory_release(test_allocator);
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
  free(test_allocator);
}
