test( reflection_path_print, empty ) {

  given("an empty reflection");
    struct reflection rfx = { 0 };


  calling("reflection_path_print()");
    char result[128] = { 0 };
    i32 printed_bytes = reflection_path_print(&rfx, result, sizeof(result));


  must("print an empty path");
    verify(printed_bytes == 0);
    verify(streq(result, ""));


  success();
}
