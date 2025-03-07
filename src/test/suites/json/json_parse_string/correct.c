test( json_parse_string, correct ) {

  given("a json string");
    char* json;


  when("the string is correct");
    json = "\"exam ple\"";


  calling("json_parse_string()");
    struct io input = io_open_memory(json, strlen(json));
    u64 string_length = json_parse_string(&input);


  must("parse the string correctly");
    verify(error.occurred == false);
    verify(string_length == 10);


  success();
}
