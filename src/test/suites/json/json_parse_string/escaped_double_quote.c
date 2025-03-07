test( json_parse_string, escaped_double_quote ) {

  given("a json string");
    char* json;


  when("the string is escaped with a double quote");
    json = "\"exam\\\"ple\"";


  calling("json_parse_string()");
    struct io input = io_open_memory(json, strlen(json));
    u64 string_length = json_parse_string(&input);


  must("parse the string correctly");
    verify(error.occurred == false);
    verify(string_length == 11);


  success();
}
