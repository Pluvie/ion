test( json_parse_number, error_oct ) {

  given("a json number");
    char* json;


  when("the number is octal");
    json = "02250";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    i32 number;
    json_parse_number(&input, I32, &number);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "octal numbers are not valid JSON"));


  success();
}
