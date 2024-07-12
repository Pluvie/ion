test( json_parse_number, error_exponent ) {

  given("a json number");
    char* json;


  when("the number has an invalid exponent");
    json = "123.4eXX";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    struct failure error = { 0 };
    json_parse_number(&input, &error);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected an exponent"));


  success();
}
