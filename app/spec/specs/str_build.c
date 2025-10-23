#include "str_build.h"

spec( str_build ) {
  argument(struct str_builder* builder);
  argument(str value);

  precondition("a valid string builder");
    #define preconditions \
      builder = allocator_push(spec_allocator, sizeof(*builder)); \
      *builder = str_builder(32);

  when("the builder has enough capacity to append the value string") {
    value = string("example");
    apply(preconditions);

    unsigned int previous_builder_capacity = builder->capacity;
    str_build(builder, value);

    must("append the value to the builder");
      verify(str_equal(builder->result, value));

    must("not increase the builder capacity");
      verify(builder->capacity == previous_builder_capacity);

    success();
      memory_release(builder->memory);
  } end();

  when("the builder has not enough capacity to append the value string") {
    value = string("example very very very very very very long");
    apply(preconditions);

    unsigned int previous_builder_capacity = builder->capacity;
    str_build(builder, value);

    must("append the value to the builder");
      verify(str_equal(builder->result, value));

    must("double the builder capacity");
      verify(builder->capacity == 2 * previous_builder_capacity);

    success();
      memory_release(builder->memory);
  } end();
}
