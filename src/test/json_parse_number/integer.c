test( json_parse_number, integer ) {

  given("a json number");
    char* json;


  when("the number is an integer");
    json = "1245";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("parse the number correctly");
    verify(error.occurred == false);
    i32 result; sci_notation_convert(&number, I32, &result);
    verify(result == 1245);
    verify(is_number == true);


  success();
}
