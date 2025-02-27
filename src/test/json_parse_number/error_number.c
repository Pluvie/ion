test( json_parse_number, error_number ) {

  given("a json number");
    char* json;


  when("the number is not a number");
    json = "abc";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected a number"));
    verify(is_number == false);


  success();
}
