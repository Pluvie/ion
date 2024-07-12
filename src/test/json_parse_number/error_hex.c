test( json_parse_number, error_hex ) {

  given("a json number");
    char* json;


  when("the number is hexadecimal");
    json = "0xff";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    struct failure error = { 0 };
    json_parse_number(&input, &error);


  must("fail to parse the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "hexadecimal numbers are not valid JSON"));


  success();
}
