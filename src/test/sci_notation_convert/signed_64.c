test( sci_notation_convert, signed_64 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is I64");
    enum types type = I64;


  when("the number is a signed integer");
    number.negative = true;
    number.integral.content = "77777777777";
    number.integral.length = 11;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(i64*) result == -77777777777);


  success();
}
