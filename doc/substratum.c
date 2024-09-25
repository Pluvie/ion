#include <ion/ion.h>
#include <time.h>

procedure_arguments(example_procedure) {
  i32 value;
};

procedure_result(example_procedure) {
  u32 example;
};

procedure(
    example_procedure
);

procedure(
    example_procedure
)
{
  result_initialize(example_procedure);
  print("The meaning of life is: %i.", args.value);
  result.example = 7;
  error.occurred = true;
  return result;
}


i32 main (
    i32 argc,
    char** argv
)
{
  allocator_create(example_allocator, 0);


  initialize(number, u32, 4);
  initialize(clocktime, u64, call(clock));

  allocate_on(example_allocator,
    ptr, u64, { 99 });
  array_allocate_on(example_allocator,
    example_array, u64, 0);
  map_allocate_on(example_allocator,
    example_map, i64, i64, 0);

  array_push(example_array, &(u64) { 18 });
  map_set(example_map, &(i64) { -7 }, &(i64) { 7 });
  map_set(example_map, &(i64) { -5 }, &(i64) { 5 });

  print("[%li] Here i am: %i (%li).",
    clocktime, number, *ptr);

  call(memcpy, ptr, &(u64) { 77 }, sizeof(u64));

  print("The ptr has changed to: %li.", *ptr);

  print("The array has: %li elements. The first is: %li.",
    example_array->length, as(u64, call(array_get, example_array, 0)));

  proc(example_procedure, { 42 }) {
    if (error.occurred)
      break;

    assign_to(number, result.example);
    print("The result %i has been returned.", number);
  }

  for array_each(example_array, u64*, element) {
    print("Element: %li.", *element);
  }

  for map_each(example_map, i64*, key, i64*, value) {
    print("Map: [%li] [%li].", *key, *value);
  }

  allocator_destroy(example_allocator);

  return EXIT_SUCCESS;
}
