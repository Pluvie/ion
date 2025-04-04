#include "../../../../src/ion.h"
#include "../../../../src/ion.c"
#include "numbers.h"

void insert (
    void
)
{
  struct memory allocator = memory_init(0);
  struct map* map = map_allocate(sizeof(i32), sizeof(i32), 0, &allocator);

  for (i32 i = 0; i < 1000000; i++) {
    map_set(map, &i, &i);
  }

  print("Done: %i", as(i32, map_get(map, &(i32) { 999999 })));
  memory_release(&allocator);
}

void lookup (
    void
)
{
  struct memory allocator = memory_init(0);
  struct map* map = map_allocate(sizeof(i32), sizeof(i32), 0, &allocator);

  for (i32 i = 0; i < countof(numbers); i++) {
    map_set(map, &numbers[i], &i);
  }

  i32 v;
  for (i32 j = 0; j < 10000; j++) {
    for (i32 i = 0; i < countof(numbers); i++) {
      v = as(i32, map_get(map, &numbers[i]));
    }
  }

  print("Size: %li", map->length);
  print("LF: %f", (d64) map->length / (d64) map->capacity);
  print("Buckets: %li", map->capacity);
  print("Done: %i", v);
  memory_release(&allocator);
}

i32 main (
    i32 argc,
    char** argv
)
{
  insert();
  //lookup();
  return EXIT_SUCCESS;
}
