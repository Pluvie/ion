test( sci_notation_convert, unsigned_consistency ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is unsigned");
    enum types type = U64;


  when("the number is a negative integer");
    number.negative = true;
    number.integer.content = "100";
    number.integer.length = 3;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert to (U64): number is negative"));


  success();
}
