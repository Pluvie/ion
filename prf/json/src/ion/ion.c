#include <ion.h>
#include <ion.c>

#include "ion.h"

struct coordinate calc (
    str* json,
    struct allocator* allocator
)
{
  struct coordinate result = { 0 };
  struct coordinates_data data = { 0 };

  json_decode(json, &data, &coordinates_data_reflection, allocator);
  if (unlikely(failure.occurred))
    print("json decode error: ", failure.message);

  printl("coordinates found: ", f(data.coordinates.length));
  return result;
}

int0 main (
    int0 argc,
    char** argv
)
{

  struct allocator allocator = allocator_init(0);

  void* file = fopen("exe/benchmark.json", "r");
  unsigned int file_size = 0;
  fseek(file, 0L, SEEK_END);
  file_size = ftell(file);
  rewind(file);

  str json = { allocator_push(&allocator, next_mul2(file_size, 64)), file_size };
  int file_read_result = fread(json.chars, file_size, 1, file);
  if (file_read_result < 0) {
    print("cannot read from file");
    return EXIT_FAILURE;
  }

  /*
  str p = { json.chars, 100 };
  printl(">>>>> read: ", f(p));
  */

  struct coordinate result = calc(&json, &allocator);
  printl("Result: { x: ", f(result.x), ", y: ", f(result.y),", z: ", f(result.z), " }");

  allocator_release(&allocator);
  return EXIT_SUCCESS;
}
