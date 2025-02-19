test( sci_notation_convert, signed_64_underflow ) {

  given("a scientific notation conversion to I64");
    enum types type = I64;


  when("the number is an integer lesser than I64_MIN");
    struct sci_notation number = {
      .negative = true,
      .integral = s("77777777777777777777777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(i64)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message,
      "cannot convert -77777777777777777777777 to (I64): value overflow"));


  success();
}
