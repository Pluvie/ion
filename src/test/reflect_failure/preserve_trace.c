#include "./preserve_trace_failing_function.c"

test( reflect_failure, preserve_trace ) {

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


  calling("reflect_failure()");
  must("preserve the correct error trace");
    verify(error.occurred == true);
    verify(error.trace_count == 2);
    verify(streq(error.trace[0].file,
      "./src/ion/functions/io_write.c"));
    verify(error.trace[0].line == 17);
    verify(streq(error.trace[1].file,
      "./src/test/reflect_failure/./preserve_trace_failing_function.c"));
    verify(error.trace[1].line == 9);


  success();
}
