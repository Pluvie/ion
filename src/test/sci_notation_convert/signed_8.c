test( sci_notation_convert, signed_8 ) {

  given("a scientific notation conversion to I8");
    enum types type = I8;


  when("the number is a signed integer");
    struct sci_notation number = {
      .negative = true,
      .integral = s("77"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(i8)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(i8*) result == -77);


  success();
}
