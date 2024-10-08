test( sci_notation_convert, signed_8_overflow ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is I8");
    enum types type = I8;


  when("the number is an integer greater than I8_MAX");
    number.integer.content = "300";
    number.integer.length = 3;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert +300 to (I8): value overflow"));


  success();
}
