test( json_parse_number, error_fractional ) {

  given("a json number");
    char* json;


  when("the number has an invalid fractional");
    json = "123.XX";


  calling("json_parse_number()");
    struct io input = io_open_memory(json, strlen(json));
    u64 number_length = json_parse_number(&input);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected a digit after the decimal separator"));
    verify(number_length == 0);


  success();
}
