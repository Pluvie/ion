test( sci_notation_convert, unsigned_consistency ) {

  given("a scientific notation conversion to an unsigned type");
    enum types type = U64;


  when("the number is a negative integer");
    struct sci_notation number = {
      .negative = true,
      .integral = s("100"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(u64)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert to (U64): number is negative"));


  success();
}
