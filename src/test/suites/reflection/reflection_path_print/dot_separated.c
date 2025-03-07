test( reflection_path_print, dot_separated ) {

  given("a reflection with named fields");
    struct example {
      u64 index;
      u64 value;
      struct { 
        i32 value;
      } inner;
    };

    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(index, U64, struct example) },
        { field(value, U64, struct example) },
        { field(inner, STRUCT, struct example), fields({
            { field(value, I32, struct example, inner) }
          })
        },
      })
    };


  when("the reflection is initialized");
    struct example object;
    reflection_initialize(&rfx, &object, NULL);


  when("a supposed error is found in an inner element");
    struct reflection* inner_rfx = vector_get(rfx.fields, 2);
    struct reflection* inner_value_rfx = vector_get(inner_rfx->fields, 0);


  calling("reflection_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = reflection_path_print(inner_value_rfx, result, sizeof(result));


  must("print a dot separated path");
    verify(printed_bytes == strlen("inner.value"));
    verify(streq(result, "inner.value"));


  success();
}
