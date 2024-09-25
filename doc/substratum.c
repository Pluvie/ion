#include <ion/ion.h>
#include <time.h>

__thread struct failure error = { 0 };




#define procedure_arguments(procedure)      \
  struct arguments__ ## procedure

#define procedure_result(procedure)         \
  struct result__ ## procedure

#define procedure(procedure) \
  struct result__ ## procedure procedure (  \
      struct arguments__ ## procedure args \
  )

#define result_initialize(procedure) \
  struct result__ ## procedure result = { 0 };

#define proc_initializer(procedure, ...) \
  for (struct result__ ## procedure result = procedure(__VA_OPT__((struct arguments__ ## procedure) __VA_ARGS__))

#define proc(procedure, ...) \
  u32 lvar(call) = 0; proc_initializer(procedure __VA_OPT__(, __VA_ARGS__)); lvar(call) == 0; lvar(call) = 1)

#define initialize(variable, type, ...)                                                 \
  type variable = (type) { 0 };                                                         \
  __VA_OPT__(variable = __VA_ARGS__)

#define allocate(pointer, type, ...)                                                    \
  type* pointer = malloc(sizeof(type));                                                 \
  __VA_OPT__(*pointer = (type) __VA_ARGS__)

#define allocate_on(allocator, pointer, type, ...)                                      \
  type* pointer = memory_alloc_zero(allocator, sizeof(type));                           \
  __VA_OPT__(*pointer = (type) __VA_ARGS__)

#define allocator_create(name, initial_capacity)                                        \
  struct memory* name = malloc(sizeof(struct memory));                                  \
  *name = memory_init(initial_capacity)

#define allocator_release(name)                                                         \
  memory_release(name)

#define allocator_destroy(name)                                                         \
  memory_release(name);                                                                 \
  free(name)

#define array_allocate_on(allocator, name, type, initial_capacity)                      \
  struct array* name = memory_alloc(allocator, sizeof(struct array));                   \
  *name = array_init(sizeof(type), initial_capacity, allocator)

#define map_allocate_on(allocator, name, key_type, value_type, initial_capacity)        \
  struct map* name = memory_alloc(allocator, sizeof(struct array));                     \
  *name = map_init(sizeof(key_type), sizeof(value_type), initial_capacity, allocator)

#define assign(value, target) \
  target = value

#define call(function, ...) \
  function(__VA_OPT__(__VA_ARGS__))




procedure_arguments(example_procedure) {
  i32 value;
};

procedure_result(example_procedure) {
  u32 example;
};

procedure(example_procedure);

procedure(example_procedure)
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

    assign(result.example, number);
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
