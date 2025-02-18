test( sci_notation_convert, signed_64_underflow ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is I64");
    enum types type = I64;


  when("the number is an integer lesser than I64_MIN");
    number.negative = true;
    number.integral.content = "77777777777777777777777";
    number.integral.length = 23;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message,
      "cannot convert -77777777777777777777777 to (I64): value overflow"));


  success();
}
