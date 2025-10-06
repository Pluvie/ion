#include "spec.h"
#include "spec.c"

#include <ion.c>

spec( allocator_init );
spec( allocator_pop );
spec( allocator_push );
spec( allocator_release );
spec( allocator_reset );
spec( list );
spec( list_alloc );
spec( list_at );
spec( list_each );
spec( list_init );
spec( list_pop );
spec( list_init );
spec( list_reflection_adder );
spec( list_reflection_creator );
spec( list_push );
spec( fail );
spec( fatal );
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
spec( reflection );
spec( set );
spec( set_add );
spec( set_alloc );
spec( set_init );
spec( set_pos );

int0 main (
    int0 argc,
    char** argv
)
{
  spec_add( allocator_init );
  spec_add( allocator_pop );
  spec_add( allocator_push );
  spec_add( allocator_release );
  spec_add( allocator_reset );
  spec_add( list );
  spec_add( list_alloc );
  spec_add( list_at );
  spec_add( list_each );
  spec_add( list_init );
  spec_add( list_pop );
  spec_add( list_init );
  spec_add( list_reflection_adder );
  spec_add( list_reflection_creator );
  spec_add( list_push );
  spec_add( fail );
  spec_add( fatal );
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
  spec_add( reflection );
  spec_add( set );
  spec_add( set_add );
  spec_add( set_alloc );
  spec_add( set_init );
  spec_add( set_pos );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
