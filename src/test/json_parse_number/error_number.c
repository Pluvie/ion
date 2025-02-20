test( json_parse_number, error_number ) {

  given("a json number");
    char* json;


  when("the number is not a number");
    json = "abc";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    i32 number;
    json_parse_number(&input, I32, &number);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "expected a number"));


  success();
}
