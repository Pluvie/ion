#include <test.h>

i32 main (
    i32 argc,
    char** argv
)
{
  original_stderr = fdopen(STDERR_FILENO, "w");
  suppressed_stderr = fopen("/dev/null", "w");

  test_suite();

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

  fclose(suppressed_stderr);
  fclose(original_stderr);

  if (suite_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
