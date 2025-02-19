test( sci_notation_convert, integer_consistency_exponent ) {

  given("a scientific notation conversion to I64");
    enum types type = I64;


  when("the number has a exponent");
    struct sci_notation number = {
      .negative = true,
      .integral = s("100"),
      .exponent = s("33"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(i64)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert to (I64): number has an exponent"));


  success();
}
