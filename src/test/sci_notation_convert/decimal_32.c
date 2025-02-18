test( sci_notation_convert, decimal_32 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is D32");
    enum types type = D32;


  when("the number is a decimal");
    number.negative = true;
    number.integral.content = "77";
    number.integral.length = 2;
    number.fractional.content = "55";
    number.fractional.length = 2;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(approx_eq(*(d32*) result, (d32) -77.55) == true);


  success();
}
