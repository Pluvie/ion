test( reflect_path_print, dot_separated ) {

  given("a schema with named fields");
    struct example {
      u64 index;
      u64 value;
      struct example_inner { 
        i32 value_inner;
      } inner;
    };

    struct reflect schema = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, index), type(U64) },
        { field(struct example, value), type(U64) },
        { field(struct example, inner),
            type(STRUCT, sizeof(struct example_inner)), fields({
              { field(struct example_inner, value_inner), type(I32) }
            })
        },
      })
    };


  when("the schema is initialized");
    reflect_initialize(&schema);
    struct reflect* schema_inner = vector_get(schema.child, 2);
    struct reflect* schema_inner_value_inner = vector_get(schema_inner->child, 0);


  calling("reflect_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = reflect_path_print(
      schema_inner_value_inner, result, sizeof(result));


  must("print a dot separated path");
    verify(printed_bytes == strlen("inner.value_inner"));
    verify(streq(result, "inner.value_inner"));


  success();
}
