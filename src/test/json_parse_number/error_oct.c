test( json_parse_number, error_oct ) {

  given("a json number");
    char* json;


  when("the number is octal");
    json = "02250";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("not fail to parse the number but return false");
    verify(error.occurred == false);
    verify(is_number == false);


  success();
}
