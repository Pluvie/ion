test( protocol_path_print, index ) {

  given("a schema with named and indexed fields");
    struct example {
      u64 index;
      u64 value;
      struct example_inner { 
        i32 value_inner;
      } inner[3];
    };

    struct reflect schema_inner = {
      type(STRUCT, sizeof(struct example_inner)), fields({
        { field(struct example_inner, value_inner), type(I32) }
      })
    };

    struct reflect schema = {
      type(STRUCT, sizeof(struct example)), fields({
        { field(struct example, index), type(U64) },
        { field(struct example, value), type(U64) },
        { field(struct example, inner), type(SEQUENCE, 3), of({
            type(STRUCT), schema(&schema_inner)
          })
        },
      })
    };


  when("a protocol is initialized on that schema");
    struct reflect* schema_sequence = vector_get(schema.child, 2);
    schema_sequence->parent = &schema;
    struct reflect* schema_sequence_inner = vector_get(schema_sequence->child, 0);
    schema_sequence_inner->index = 2;
    schema_sequence_inner->parent = schema_sequence;
    struct reflect* schema_sequence_inner_value_inner = vector_get(schema_sequence_inner->child, 0);
    schema_sequence_inner_value_inner->parent = schema_sequence_inner;


    struct memory allocator = memory_init(4096);
    struct protocol proto = {
      .schema = vector_get(schema_sequence_inner->child, 0),
      .allocator = &allocator
    };


  calling("protocol_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = protocol_path_print(&proto, result, sizeof(result));


  must("print a dot separated path with names and indexes");
    verify(printed_bytes == strlen("inner.2.value_inner"));
    verify(streq(result, "inner.2.value_inner"));


  success();
    memory_release(&allocator);
}
