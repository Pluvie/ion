test( reflect_path_print, index ) {

  given("a reflection with named and indexed fields");
    struct example {
      u64 index;
      u64 value;
      struct example_inner { 
        i32 value_inner;
      } inner[3];
    };

    struct reflect reflection_inner = {
      type(STRUCT, sizeof(struct example_inner)), fields({
        { field(struct example_inner, value_inner), type(I32) }
      })
    };

    struct reflect reflection = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, index), type(U64) },
        { field(struct example, value), type(U64) },
        { field(struct example, inner), type(SEQUENCE, 3), of({
            type(STRUCT), reflect(&reflection_inner)
          })
        },
      })
    };


  when("the reflection is initialized");
    reflect_initialize(&reflection);


  when("a supposed error is found in an indexed element");
    struct reflect* reflection_sequence =
      vector_get(reflection.child, 2);
    struct reflect* reflection_sequence_inner =
      vector_get(reflection_sequence->child, 0);
    struct reflect* reflection_sequence_inner_value_inner =
      vector_get(reflection_sequence_inner->child, 0);

    reflection_sequence_inner->index = 2;


  calling("reflect_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = reflect_path_print(
      reflection_sequence_inner_value_inner, result, sizeof(result));


  must("print a dot separated path with names and indexes");
    verify(printed_bytes == strlen("inner.2.value_inner"));
    verify(streq(result, "inner.2.value_inner"));


  success();
}
