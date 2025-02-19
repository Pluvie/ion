test( sci_notation_convert, unsigned_8 ) {

  given("a scientific notation conversion to U8");
    enum types type = U8;


  when("the number is an integer");
    struct sci_notation number = {
      .integral = s("123"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(u8)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(u8*) result == 123);


  success();
}
