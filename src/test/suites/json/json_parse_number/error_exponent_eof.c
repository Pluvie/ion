test( json_parse_number, error_exponent_eof ) {

  given("a json number");
    char* json;


  when("the number is missing an exponent");
    json = "123.4e";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected sign or digit after exponent"));
    verify(is_number == false);


  success();
}
