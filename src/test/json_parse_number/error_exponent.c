test( json_parse_number, error_exponent ) {

  given("a json number");
    char* json;


  when("the number has an invalid exponent");
    json = "123.4eXX";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    d32 number;
    json_parse_number(&input, D32, &number);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected sign or digit after exponent"));


  success();
}
