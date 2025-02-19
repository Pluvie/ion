test( sci_notation_convert, signed_16_underflow ) {

  given("a scientific notation conversion to I16");
    enum types type = I16;


  when("the number is an integer lesser than I16_MIN");
    struct sci_notation number = {
      .negative = true,
      .integral = s("77777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(i16)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert -77777 to (I16): value overflow"));


  success();
}
