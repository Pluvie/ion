test( sci_notation_convert, unsigned_8_overflow ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is U8");
    enum types type = U8;


  when("the number is an integer greater than U8_MAX");
    number.integral.content = "300";
    number.integral.length = 3;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 300 to (U8): value overflow"));


  success();
}
