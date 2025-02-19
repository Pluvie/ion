test( sci_notation_convert, signed_64 ) {

  given("a scientific notation conversion to I64");
    enum types type = I64;


  when("the number is a signed integer");
    struct sci_notation number = {
      .negative = true,
      .integral = s("77777777777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(i64)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(i64*) result == -77777777777);


  success();
}
