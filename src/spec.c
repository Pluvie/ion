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

  int number = 999'999'999'999'999;
  int other = 1e15;
  dec decimal = 1.7e-3;

  print("my number is: ", f(number), " or ", f(other), " or even: ", f(decimal));

  printf("my number is: %lli or %lli or even: %f\n", number, other, decimal);

  return EXIT_SUCCESS;
}
