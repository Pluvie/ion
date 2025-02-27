test( json_parse_number, error_fractional_eof ) {

  given("a json number");
    char* json;


  when("the number is missing the fractional part");
    json = "123.";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected a digit after the decimal separator"));
    verify(is_number == false);


  success();
}
