test( sci_notation_convert, decimal_64 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is D64");
    enum types type = D64;


  when("the number is a decimal");
    number.negative = true;
    number.integer.content = "77";
    number.integer.length = 2;
    number.mantissa.content = "55";
    number.mantissa.length = 2;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(approx_eq(*(d64*) result, (d64) -77.55) == true);


  success();
}
