#include "spec.h"

spec( memory_acquire );
spec( memory_release );
spec( memory_resize );

int0 main (
    int0 argc,
    char** argv
)
{
  spec_add( memory_acquire );
  spec_add( memory_release );
  spec_add( memory_resize );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
