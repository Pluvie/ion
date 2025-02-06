test( reflect_path_print, empty ) {

  given("an empty reflection");
    struct reflect reflection = { 0 };


  when("the reflection is initialized");
    reflect_initialize(&reflection)


  calling("reflect_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = reflect_path_print(&reflection, result, sizeof(result));


  must("print an empty path");
    verify(printed_bytes == 0);
    verify(streq(result, ""));


  success();
}
