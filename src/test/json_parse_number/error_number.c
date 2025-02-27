test( json_parse_number, error_number ) {

  given("a json number");
    char* json;


  when("the number is not a number");
    json = "abc";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("not fail to parse the number but return false");
    verify(error.occurred == false);
    verify(is_number == false);


  success();
}
