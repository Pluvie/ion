#include "preserve_trace_failing_function.c"

test( error_add_reflection_path, preserve_trace ) {

  given("a reflection");
    struct example {
      u64 value;
    };

    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(value, U64, struct example) },
      })
    };


  when("a supposed error is found");
    struct reflection* field_rfx = vector_get(rfx.fields, 0);
    field_rfx->parent = &rfx;
    preserve_trace_failing_function(field_rfx);


  calling("error_add_reflection_path()");
  must("preserve the correct error trace");
    verify(error.occurred == true);
    verify(error.trace_count == 1);
    verify(streq(error.trace[0].file,
      "src/test/suites/../../ion/modules/io/functions/io_write_memory.c"));
    verify(error.trace[0].line == 9);


  success();
}
