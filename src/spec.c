#include "spec.h"

spec( memory_acquire );

int0 main (
    int0 argc,
    char** argv
)
{
  /*
  void* address = memory_acquire(1024);
  address = memory_resize(address, 2048);
  memory_release(address);
  if (spec__memory_acquire())
    printf("success");
  else
    printf("fail");

  printl("hey printing works ", f((int) { 100 }), "%!!!");
  printf("sizeof int: %li\n", sizeof(int));

  return EXIT_SUCCESS;
  */

  spec_focus( memory_acquire );

  specs_run();

  if (specs_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
