test( json_parse_number, error_eof ) {

  given("a json number");
    char* json;


  when("the number is not completed");
    json = "";


  calling("json_parse_number()");
    struct io input = io_open_memory(json, strlen(json));
    u64 number_length = json_parse_number(&input);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "io: end of memory reached"));
    verify(number_length == 0);


  success();
}
