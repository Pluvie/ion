test( sci_notation_convert, unsigned_32 ) {

  given("a scientific notation conversion to U32");
    enum types type = U32;


  when("the number is an integer");
    struct sci_notation number = {
      .integral = s("77777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(u32)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(u32*) result == 77777);


  success();
}
