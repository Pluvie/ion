test( sci_notation_convert, integer_consistency_exponent ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is integer");
    enum types type = I64;


  when("the number has a exponent");
    number.negative = true;
    number.integral.content = "100";
    number.integral.length = 3;
    number.exponent.content = "33";
    number.exponent.length = 2;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert to (I64): number has an exponent"));


  success();
}
