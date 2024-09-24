#include <ion/ion.h>



#define function_arguments(function)      \
  struct arguments__ ## function

#define function_result(function)         \
  struct result__ ## function

#define function(function) \
  struct result__ ## function function (  \
      struct arguments__ ## function args \
  )

#define result_initialize(function) \
  struct result__ ## function result = { 0 };

#define call_initializer(function, ...) \
  for (struct result__ ## function result = function(__VA_OPT__((struct arguments__ ## function) __VA_ARGS__))

#define call(function, ...) \
  u32 lvar(call) = 0; call_initializer(function __VA_OPT__(, __VA_ARGS__)); lvar(call) == 0; lvar(call) = 1)

#define initialize(variable, type, ...) \
  type variable __VA_OPT__(= __VA_ARGS__);

#define allocate(pointer, type, ...)    \
  type* pointer = malloc(sizeof(type)); \
  __VA_OPT__(memcpy(pointer, &(type) __VA_ARGS__, sizeof(type));)




function_arguments(procedure_allocate) {
  i32 value;
};

function_result(procedure_allocate) {
  u32 example;
};

function(procedure_allocate);

function(procedure_allocate)
{
  result_initialize(procedure_allocate);
  print("The meaning of life is: %i.", args.value);
  result.example = 7;
  return result;
}




i32 main (
    i32 argc,
    char** argv
)
{
  initialize(number, u32, 4);
  allocate(ptr, u32, { 12 });
  allocate(scrap, u64, { 99 });

  print("Here i am: %i (%i) (%li).", number, *ptr, *scrap);

  call(procedure_allocate, { 42 }) {
    number = result.example;
    print("The result %i has been returned.", number);
  }

  return EXIT_SUCCESS;
}
