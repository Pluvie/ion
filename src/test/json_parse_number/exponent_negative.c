test( json_parse_number, exponent_negative ) {

  given("a json number");
    char* json;


  when("the number has a negative exponent");
    json = "1245.678e-5";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    d64 number;
    json_parse_number(&input, D64, &number);


  must("parse the number correctly");
    verify(error.occurred == false);
    verify(approx_eq(number, (d64) 0.01245678) == true);


  success();
}
