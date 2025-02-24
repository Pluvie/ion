#include "preserve_trace_failing_function.c"

test( error_add_reflection_path, preserve_trace ) {

  given("a reflection");
    struct example {
      u64 value;
    };

    struct reflect reflection = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, value), type(U64) },
      })
    };


  when("the reflection is initialized");
    reflect_initialize(&reflection);


  when("a supposed error is found");
    struct reflect* reflection_inner = vector_get(reflection.child, 0);
    preserve_trace_failing_function(reflection_inner);


  calling("error_add_reflection_path()");
  must("preserve the correct error trace");
    verify(error.occurred == true);
    verify(error.trace_count == 1);
    verify(streq(error.trace[0].file,
      "./src/ion/functions/io_write.c"));
    verify(error.trace[0].line == 17);


  success();
}
