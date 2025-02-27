test( json_parse_number, error_hex ) {

  given("a json number");
    char* json;


  when("the number is hexadecimal");
    json = "0xff";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "hexadecimal numbers are not valid JSON"));
    verify(is_number == false);


  success();
}
