test( json_parse_number, fractional_negative ) {

  given("a json number");
    char* json;


  when("the number is a negative decimal");
    json = "-1245.678";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    d32 number;
    json_parse_number(&input, D32, &number);


  must("parse the number correctly");
    verify(error.occurred == false);
    verify(approx_eq(number, (d32) -1245.678) == true);


  success();
}
