test( json_parse_number, exponent ) {

  given("a json number");
    char* json;


  when("the number has an exponent");
    json = "1245.678e12";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    d64 number;
    json_parse_number(&input, D64, &number);


  must("parse the number correctly");
    verify(error.occurred == false);
    verify(approx_eq(number, (d64) 1245678000000000) == true);


  success();
}
