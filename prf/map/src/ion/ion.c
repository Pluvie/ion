#include <ion.h>
#include <ion.c>

#include "ion.h"

void insert (
    void
)
{
  struct allocator allocator = allocator_init(0);
  struct int_map map = int_map_alloc(0, &allocator);
  int i;
  int* v;

  for (i = 0; i < 1000000; i++)
    int_map_set(&map, i, i);

  v = int_map_get(&map, 999999);
  printf("Done: %"fmt(INT)"\n", *v);

  allocator_release(&allocator);
}

void lookup (
    void
)
{
  struct allocator allocator = allocator_init(1024*1024);
  struct int_map map = int_map_alloc(1024*1024, &allocator);
  int i, j;
  int* v;

  for (j = 0; j < 1000; j++)
    for (i = 0; i < 1000; i++)
      int_map_set(&map, numbers[i] + j, i);

  for (j = 0; j < 1000; j++)
    for (i = 0; i < 1000; i++)
      v = int_map_get(&map, numbers[i] + j);

  printf("Done: %"fmt(INT)"\n", *v);
  allocator_release(&allocator);
}

int_t main (
    int_t argc,
    cstr* argv
)
{
  /*insert();*/
  lookup();
  return EXIT_SUCCESS;
}
