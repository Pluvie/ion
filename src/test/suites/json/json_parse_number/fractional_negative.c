test( json_parse_number, fractional_negative ) {

  given("a json number");
    char* json;


  when("the number is a negative decimal");
    json = "-1245.678";


  calling("json_parse_number()");
    struct io input = io_open_memory(json, strlen(json));
    u64 number_length = json_parse_number(&input);


  must("parse the number correctly");
    verify(error.occurred == false);
    verify(number_length == 9);


  success();
}
