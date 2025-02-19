test( sci_notation_convert, unsigned_16_overflow ) {

  given("a scientific notation conversion to U16");
    enum types type = U16;


  when("the number is an integer greater than U16_MAX");
    struct sci_notation number = {
      .integral = s("77777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(u16)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 77777 to (U16): value overflow"));


  success();
}
