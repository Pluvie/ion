test( json_parse_number, exponent_negative ) {

  given("a json number");
    char* json;


  when("the number has a negative exponent");
    json = "1245.678e-5";


  calling("json_parse_number()");
    struct io input = io_open_memory(json, strlen(json));
    u64 number_length = json_parse_number(&input);


  must("parse the number correctly");
    verify(error.occurred == false);
    verify(number_length == 11);


  success();
}
