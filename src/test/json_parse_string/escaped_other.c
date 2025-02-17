test( json_parse_string, escaped_other ) {

  given("a json string");
    char* json;


  when("the string is escaped with another character");
    json = "\"exam\tple\"";


  calling("json_parse_string()");
    struct io input = io_reader(json, strlen(json));
    struct string result = json_parse_string(&input);


  must("parse the string correctly");
    verify(error.occurred == false);
    verify(strneq(result.content, "\"exam\tple\"", result.length));


  success();
}
