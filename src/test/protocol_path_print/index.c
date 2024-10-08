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
      type(STRUCT, { sizeof(struct example_inner), 1 }) {
        { field(value_inner, struct example_inner), type(I32) }
      }
    };

    struct reflect schema = {
      type(STRUCT, { sizeof(struct example), 3 }) {
        { field(index, struct example), type(U64) },
        { field(value, struct example), type(U64) },
        { field(inner, struct example), type(SEQUENCE, 3)
          {{ schema(&schema_inner) }},
        },
      }
    };


  when("a protocol is initialized on that schema");
    struct reflect* schema_sequence = schema.child + 2;
    schema_sequence->parent = &schema;
    struct reflect* schema_sequence_inner = schema_sequence->child;
    schema_sequence_inner->index = 2;
    schema_sequence_inner->parent = schema_sequence;
    schema_sequence_inner->child->parent = schema_sequence_inner;


    struct memory allocator = memory_init(4096);
    struct protocol proto = {
      .schema = schema_sequence_inner->child,
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
