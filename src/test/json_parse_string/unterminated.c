test( json_parse_string, unterminated ) {

  given("a json string");
    char* json;


  when("the string is not terminated");
    json = "\"exam ple";


  calling("json_parse_string()");
    struct io input = io_reader(json, strlen(json));
    struct string result = json_parse_string(&input);


  must("fail to parse the string with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "unterminated string: missing final '\"'"));
    verify(result.content == NULL);
    verify(result.length == 0);


  success();
}
