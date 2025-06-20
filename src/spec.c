#include "spec.h"
#include "ion.c"

int32 main (
    int32 argc,
    char** argv
)
{
  spec_add( date );
  spec_add( date_to_string );
  spec_add( date_today );
  spec_add( io_buffer_read );
  spec_add( io_read );
  spec_add( list );
  spec_add( list_init );
  spec_add( list_push );
  spec_add( time_now );
  spec_add( time_to_string );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
