test( json_parse_number, error_exponent_eof ) {

  given("a json number");
    char* json;


  when("the number is missing an exponent");
    json = "123.4e";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    struct failure error = { 0 };
    json_parse_number(&input, &error);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected an exponent but found EOF"));


  success();
}
