#include <ion.h>
#include <ion/spec.h>

#include <ion.c>
#include <ion/spec.c>

spec( example );

int_t main (
    int_t argc,
    cstr* argv
)
{
  spec_add( example );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
