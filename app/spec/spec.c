#include <ion.h>
#include <ion/spec.h>

#include <ion.c>
#include <ion/spec.c>

spec( allocator_init );
spec( allocator_pop );
spec( allocator_push );
spec( allocator_release );
spec( example );

int_t main (
    int_t argc,
    cstr* argv
)
{
  spec_add( allocator_init );
  spec_add( allocator_pop );
  spec_add( allocator_push );
  spec_add( allocator_release );
  spec_add( example );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
