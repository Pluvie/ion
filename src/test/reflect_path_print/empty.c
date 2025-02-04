test( reflect_path_print, empty ) {

  given("an empty schema");
    struct reflect schema = { 0 };


  when("the schema is initialized");
    reflect_initialize(&schema)


  calling("reflect_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = reflect_path_print(&schema, result, sizeof(result));


  must("print an empty path");
    verify(printed_bytes == 0);
    verify(streq(result, ""));


  success();
}
