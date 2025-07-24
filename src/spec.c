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
  spec_add( list_alloc );
  spec_add( list_at );
  spec_add( list_each );
  spec_add( list_init );
  spec_add( list_pop );
  spec_add( list_push );
  spec_add( map );
  spec_add( map_alloc );
  spec_add( map_del );
  spec_add( map_each );
  spec_add( map_get );
  spec_add( map_has );
  spec_add( map_init );
  spec_add( map_set );
  spec_add( set );
  spec_add( set_add );
  spec_add( set_alloc );
  spec_add( set_del );
  spec_add( set_has );
  spec_add( set_init );
  spec_add( time_now );
  spec_add( time_to_string );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
