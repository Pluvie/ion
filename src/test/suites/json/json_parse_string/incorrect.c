test( json_parse_string, incorrect ) {

  given("a json string");
    char* json;


  when("the string is not correct");
    json = "abc \"exam ple\"";


  calling("json_parse_string()");
    struct io input = io_open_memory(json, strlen(json));
    u64 string_length = json_parse_string(&input);


  must("not fail to parse the string but return false");
    verify(error.occurred == false);
    verify(string_length == 0);


  success();
}
