test( reflection_path_print, index ) {

  given("a reflection with named and indexed fields");
    struct example {
      u64 index;
      u64 value;
      struct { 
        i32 value;
      } inner[3];
    };

    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(index, U64, struct example) },
        { field(value, U64, struct example) },
        { field(inner, SEQUENCE, struct example), of({
            type(STRUCT, typeof(*o(struct example)->inner)), fields({
              { field(value, I32, typeof(*o(struct example)->inner)) }
            })
          })
        },
      })
    };


  when("a supposed error is found in an indexed element");
    struct reflection* sequence_rfx =
      vector_get(rfx.fields, 2);
    struct reflection* sequence_inner_rfx =
      sequence_rfx->element;
    struct reflection* sequence_inner_value_rfx =
      vector_get(sequence_inner_rfx->fields, 0);

    sequence_rfx->parent = &rfx;
    sequence_inner_rfx->parent = sequence_rfx;
    sequence_inner_rfx->index = 2;
    sequence_inner_value_rfx->parent = sequence_inner_rfx;


  calling("reflection_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = reflection_path_print(
      sequence_inner_value_rfx, result, sizeof(result));


  must("print a dot separated path with names and indexes");
    verify(printed_bytes == strlen("inner.2.value"));
    verify(streq(result, "inner.2.value"));


  success();
}
