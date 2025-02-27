test( json_parse_number, error_eof ) {

  given("a json number");
    char* json;


  when("the number is not completed");
    json = "";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "io: end of memory reached"));
    verify(is_number == false);


  success();
}
