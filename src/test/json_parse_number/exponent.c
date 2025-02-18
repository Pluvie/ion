test( json_parse_number, exponent ) {

  given("a json number");
    char* json;


  when("the number has an exponent");
    json = "1245.678e90";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    struct sci_notation number = json_parse_number(&input);


  must("parse the number correctly");
    error_print();
    verify(error.occurred == false);
    verify(number.negative == false);
    verify(number.negative_exponent == false);
    verify(strneq(number.integral.content, "1245", 4));
    verify(strneq(number.fractional.content, "678", 3));
    verify(strneq(number.exponent.content, "90", 3));


  success();
}
