test( json_parse_string, escaped_double_quote ) {

  given("a json string");
    char* json;


  when("the string is escaped with a double quote");
    json = "\"exam\"ple\"";


  calling("json_parse_string()");
    struct io input = io_reader(json, strlen(json));
    struct failure error = { 0 };
    struct string result = json_parse_string(&input, &error);


  must("parse the string correctly");
    verify(error.occurred == false);
    verify(strneq(result.content, "\"exam\"ple\"", result.length));


  success();
}
