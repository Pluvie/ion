test( sci_notation_convert, unsigned_32_overflow ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is U32");
    enum types type = U32;


  when("the number is an integer greater than U32_MAX");
    number.integer.content = "77777777777";
    number.integer.length = 11;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 77777777777 to (U32): value overflow"));


  success();
}
