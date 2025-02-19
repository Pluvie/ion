test( sci_notation_convert, signed_32 ) {

  given("a scientific notation conversion to I32");
    enum types type = I32;


  when("the number is a signed integer");
    struct sci_notation number = {
      .negative = true,
      .integral = s("77777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(i32)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(i32*) result == -77777);


  success();
}
