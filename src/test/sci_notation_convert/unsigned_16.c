test( sci_notation_convert, unsigned_16 ) {

  given("a scientific notation conversion to U16");
    enum types type = U16;


  when("the number is an integer");
    struct sci_notation number = {
      .integral = s("1234"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(u16)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(u16*) result == 1234);


  success();
}
