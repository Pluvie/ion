#include "spec.h"
#include "ion.c"

int0 main (
    int0 argc,
    char** argv
)
{
  void* address = memory_require(1024, 0);
  address = memory_resize(address, 2048, 0);
  memory_release(address);
  return EXIT_SUCCESS;
}
