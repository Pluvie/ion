#include "test.h"
#include "test/suite.c"

i32 main (
    i32 argc,
    char** argv
)
{
  if (!suite_register(argc, argv))
    return EXIT_FAILURE;

  suite_run();

  if (suite_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
