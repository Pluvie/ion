test( json_parse_number, mantissa_negative ) {

  given("a json number");
    char* json;


  when("the number is a negative decimal");
    json = "-1245.678";


  calling("json_parse_number()");
    struct io input = io_reader(json, strlen(json));
    struct failure error = { 0 };
    struct sci_notation number = json_parse_number(&input, &error);


  must("parse the number correctly");
    verify(error.occurred == false);
    verify(number.negative == true);
    verify(strneq(number.integer.content, "1245", 4));
    verify(strneq(number.mantissa.content, "678", 3));


  success();
}
