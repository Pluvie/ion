#include "../../../../src/ion.h"
#include "../../../../src/ion.c"

void insert (
    void
)
{
  struct memory allocator = memory_init(0);
  struct map* map = map_allocate(sizeof(i32), sizeof(i32), 0, &allocator);

  for (int i = 0; i < 1000000; i++) {
    map_set(map, &i, &i);
  }

  print("Done: %i", as(i32, map_get(map, &(i32) { 999999 })));
  memory_release(&allocator);
}

i32 main (
    i32 argc,
    char** argv
)
{
  insert();
  return EXIT_SUCCESS;
}
