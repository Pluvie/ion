#include "../src/ion.h"
#include "../src/ion.c"

struct coordinate {
  dec x;
  dec y;
  dec z;
};

#define list_of struct coordinate
#include "ion/types/list.h"

#undef list_function
#define list_function(s, f, ...)                              \
  _Generic(*(s),                                              \
    list<struct coordinate> : list<struct coordinate>_ ## f,  \
    _list_function(v, f, __VA_ARGS__)                         \
  )

struct coordinates_data {
  list<struct coordinate>* coordinates;
};

struct reflection rfx = {
  type(STRUCT, struct coordinates_data), fields({
    { field(coordinates, POINTER, struct coordinates_data), of({
        type(LIST), container(list<struct coordinate>_), of({
          type(STRUCT, struct coordinate), fields({
            { field(x, DEC, struct coordinate) },
            { field(y, DEC, struct coordinate) },
            { field(z, DEC, struct coordinate) },
          })
        })
      })
    },
  })
};

struct coordinate calc (
    string* content,
    memory* allocator
)
{
  struct coordinate result = { 0 };
  struct coordinates_data data = { 0 };
  //struct io json = io_open(content, &rfx, allocator);
  struct io json = io_open(content, NULL, allocator);
  json_decode(&json, &data);
  if (unlikely(failure.occurred)) {
    failure_add_io_info(json.direct);
    failure_print();
  }
  return result;
}

int32 main (
    int32 argc,
    char** argv
)
{

  memory allocator = memory_init(0);

  struct file benchmark_file = file_open(s("exe/benchmark.json"));
  int size = file_size(&benchmark_file);
  string benchmark_content = { memory_alloc(&allocator, next_mul64(size)), size };
  file_read(&benchmark_file, benchmark_content.pointer, size);

  struct coordinate result = calc(&benchmark_content, &allocator);
  print("Result: { x: %f, y: %f, z: %f }", result.x, result.y, result.z);

  memory_release(&allocator);
  return EXIT_SUCCESS;
}
