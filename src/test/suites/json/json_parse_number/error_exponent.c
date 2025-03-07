test( json_parse_number, error_exponent ) {

  given("a json number");
    char* json;


  when("the number has an invalid exponent");
    json = "123.4eXX";


  calling("json_parse_number()");
    struct io input = io_open_memory(json, strlen(json));
    u64 number_length = json_parse_number(&input);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected sign or digit after exponent"));
    verify(number_length == 0);


  success();
}
