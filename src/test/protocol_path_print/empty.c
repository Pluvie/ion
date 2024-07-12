test( protocol_path_print, empty ) {

  given("an empty schema");
    struct reflect schema = { 0 };


  when("a protocol is initialized on that schema");
    struct memory allocator = memory_init(4096);
    struct protocol proto = { .schema = &schema, .allocator = &allocator };


  calling("protocol_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = protocol_path_print(&proto, result, sizeof(result));


  must("print an empty path");
    verify(printed_bytes == 0);
    verify(streq(result, ""));


  success();
    memory_release(&allocator);
}
