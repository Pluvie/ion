test( json_parse_number, error_eof ) {

  given("a json number");
    char* json;


  when("the number is not completed");
    json = "-";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    struct failure error = { 0 };
    json_parse_number(&input, &error);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected a number but found EOF"));


  success();
}
