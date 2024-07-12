#include <test.h>

i32 main (
    i32 argc,
    char** argv
)
{
  original_stderr = fdopen(STDERR_FILENO, "w");
  suppressed_stderr = fopen("/dev/null", "w");

  test_suite();

  fclose(suppressed_stderr);
  fclose(original_stderr);

  if (suite_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
