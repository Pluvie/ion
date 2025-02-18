test( sci_notation_convert, signed_32_overflow ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is I32");
    enum types type = I32;


  when("the number is an integer greater than I32_MAX");
    number.integral.content = "77777777777";
    number.integral.length = 11;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert +77777777777 to (I32): value overflow"));


  success();
}
