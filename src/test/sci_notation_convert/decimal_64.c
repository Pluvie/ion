test( sci_notation_convert, decimal_64 ) {

  given("a scientific notation conversion to D64");
    enum types type = D64;


  when("the number is a decimal");
    struct sci_notation number = {
      .negative = true,
      .integral = s("77"),
      .fractional = s("55"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(d64)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(approx_eq(*(d64*) result, (d64) -77.55) == true);


  success();
}
