test( json_parse_string, unterminated ) {

  given("a json string");
    char* json;


  when("the string is not terminated");
    json = "\"exam ple";


  calling("json_parse_string()");
    struct io input = io_memory(json, strlen(json));
    u64 string_length = 0;
    bool is_string = json_parse_string(&input, &string_length);


  must("fail to parse the string with a specific error");
    verify(error.occurred == true);
    verify(streq("io: end of memory reached", error.message));
    verify(is_string == false);
    verify(string_length == 0);


  success();
}
