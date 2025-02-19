test( sci_notation_convert, signed_32_underflow ) {

  given("a scientific notation conversion to I32");
    enum types type = I32;


  when("the number is an integer lesser than I32_MIN");
    struct sci_notation number = {
      .negative = true,
      .integral = s("77777777777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(i32)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert -77777777777 to (I32): value overflow"));


  success();
}
