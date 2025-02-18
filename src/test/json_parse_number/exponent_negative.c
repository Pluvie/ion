test( json_parse_number, exponent_negative ) {

  given("a json number");
    char* json;


  when("the number has a negative exponent");
    json = "1245.678e-90";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    struct sci_notation number = json_parse_number(&input);


  must("parse the number correctly");
    verify(error.occurred == false);
    verify(number.negative == false);
    verify(number.negative_exponent == true);
    verify(strneq(number.integral.content, "1245", 4));
    verify(strneq(number.fractional.content, "678", 3));
    verify(strneq(number.exponent.content, "90", 3));


  success();
}
