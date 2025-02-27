test( json_parse_number, exponent_negative ) {

  given("a json number");
    char* json;


  when("the number has a negative exponent");
    json = "1245.678e-5";


  calling("json_parse_number()");
    struct io input = io_memory(json, strlen(json));
    struct sci_notation number;
    bool is_number = json_parse_number(&input, &number);


  must("parse the number correctly");
    verify(error.occurred == false);
    d64 result; sci_notation_convert(&number, D64, &result);
    verify(approx_eq(result, (d64) 0.01245678) == true);
    verify(is_number == true);


  success();
}
