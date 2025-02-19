test( sci_notation_convert, unsigned_32_overflow ) {

  given("a scientific notation conversion to U32");
    enum types type = U32;


  when("the number is an integer greater than U32_MAX");
    struct sci_notation number = {
      .integral = s("77777777777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(u32)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 77777777777 to (U32): value overflow"));


  success();
}
