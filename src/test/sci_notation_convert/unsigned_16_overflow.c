test( sci_notation_convert, unsigned_16_overflow ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is U16");
    enum types type = U16;


  when("the number is an integer greater than U16_MAX");
    number.integral.content = "77777";
    number.integral.length = 5;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 77777 to (U16): value overflow"));


  success();
}
