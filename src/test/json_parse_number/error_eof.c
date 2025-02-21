test( json_parse_number, error_eof ) {

  given("a json number");
    char* json;


  when("the number is not completed");
    json = "";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    i32 number;
    json_parse_number(&input, I32, &number);


  must("fail to parse the number with a specific error");
    error_print();
    verify(error.occurred == true);
    verify(streq(error.message, "io: end of input reached"));


  success();
}
