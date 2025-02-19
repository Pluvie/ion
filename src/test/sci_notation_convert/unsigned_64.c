test( sci_notation_convert, unsigned_64 ) {

  given("a scientific notation conversion to U64");
    enum types type = U64;


  when("the number is an integer");
    struct sci_notation number = {
      .integral = s("77777777777"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(u64)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(u64*) result == 77777777777);


  success();
}
