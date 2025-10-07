#include <ion.h>
#include <ion.c>

#include "ion.h"

void insert (
    void
)
{
  struct allocator allocator = allocator_init(0);
  map<int, int> map = map_alloc(int, int, 0, &allocator);

  for (int i = 0; i < 1000000; i++)
    map_set(&map, i, i);

  int* v = map_get(&map, 999999);
  printl("Done: ", f(*v));

  allocator_release(&allocator);
}

void lookup (
    void
)
{
  struct allocator allocator = allocator_init(1024*1024);
  map<int, int> map = map_alloc(int, int, 1024*1024, &allocator);

  for (int j = 0; j < 1000; j++)
    for (int i = 0; i < 1000; i++)
      map_set(&map, numbers[i] + j, i);

  int* v;
  for (int j = 0; j < 1000; j++)
    for (int i = 0; i < 1000; i++)
      v = map_get(&map, numbers[i] + j);

  printl("Done: ", f(*v));
  allocator_release(&allocator);
}

int0 main (
    int0 argc,
    char** argv
)
{
  //insert();
  lookup();
  if (failure.occurred)
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}
