test( sci_notation_convert, signed_16 ) {

  given("a scientific notation conversion to I16");
    enum types type = I16;


  when("the number is a signed integer");
    struct sci_notation number = {
      .negative = true,
      .integral = s("777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(i16)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(i16*) result == -777);


  success();
}
