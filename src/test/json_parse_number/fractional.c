test( json_parse_number, fractional ) {

  given("a json number");
    char* json;


  when("the number is a decimal");
    json = "1245.678";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("parse the number correctly");
    verify(error.occurred == false);
    d32 result; sci_notation_convert(&number, D32, &result);
    verify(approx_eq(result, (d32) 1245.678) == true);
    verify(is_number == true);


  success();
}
