test( sci_notation_convert, unsigned_8_overflow ) {

  given("a scientific notation conversion to U8");
    enum types type = U8;


  when("the number is an integer greater than U8_MAX");
    struct sci_notation number = {
      .integral = s("300"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(u8)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 300 to (U8): value overflow"));


  success();
}
