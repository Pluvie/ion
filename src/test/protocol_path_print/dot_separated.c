test( protocol_path_print, dot_separated ) {

  given("a schema with named fields");
    struct example {
      u64 index;
      u64 value;
      struct example_inner { 
        i32 value_inner;
      } inner;
    };

    struct reflect schema = {
      type(STRUCT, { sizeof(struct example), 2 }) {
        { field(struct example, index), type(U64) },
        { field(struct example, value), type(U64) },
        { field(struct example, inner), type(STRUCT, { sizeof(struct example_inner), 1 }) {
          { field(struct example_inner, value_inner), type(I32) }
        } },
      }
    };


  when("a protocol is initialized on that schema");
    struct reflect* schema_inner = schema.child + 2;
    schema_inner->parent = &schema;
    schema_inner->child->parent = schema_inner;

    struct memory allocator = memory_init(4096);
    struct protocol proto = { .schema = schema_inner->child, .allocator = &allocator };


  calling("protocol_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = protocol_path_print(&proto, result, sizeof(result));


  must("print a dot separated path");
    verify(printed_bytes == strlen("inner.value_inner"));
    verify(streq(result, "inner.value_inner"));


  success();
    memory_release(&allocator);
}
