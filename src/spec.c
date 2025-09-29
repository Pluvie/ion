#include "spec.h"

/*
  Includes ⚡️ION⚡️ printing functions to be globally available to all specs.
*/
#include "ion/functions/print_args.c"
#include "ion/functions/print_hex.c"
#include "ion/functions/print_variadic.c"


//spec( fail );
spec( memory_acquire );
spec( memory_acquire_aligned );
spec( memory_copy );
spec( memory_release );
spec( memory_release_aligned );
spec( memory_resize );
spec( memory_set );
spec( print );
spec( printl );
spec( prints );

int0 main (
    int0 argc,
    char** argv
)
{
  //spec_add( fail );
  spec_add( memory_acquire );
  spec_add( memory_acquire_aligned );
  spec_add( memory_copy );
  spec_add( memory_release );
  spec_add( memory_release_aligned );
  spec_add( memory_resize );
  spec_add( memory_set );
  spec_add( print );
  spec_add( printl );
  spec_add( prints );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
