test( sci_notation_convert, decimal_128 ) {

  given("a scientific notation conversion to D128");
    enum types type = D128;


  when("the number is a decimal");
    struct sci_notation number = {
      .negative = true,
      .integral = s("77"),
      .fractional = s("55"),
    }


  calling("sci_notation_convert()");
    byte result[sizeof(d128)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(approx_eq(*(d128*) result, (d128) -77.55) == true);


  success();
}
