test( json_parse_number, error_oct ) {

  given("a json number");
    char* json;


  when("the number is octal");
    json = "02250";


  calling("json_parse_number()");
    struct io input = io_open_memory(json, strlen(json));
    u64 number_length = json_parse_number(&input);


  must("not fail to parse the number but return false");
    verify(error.occurred == false);
    verify(number_length == 0);


  success();
}
