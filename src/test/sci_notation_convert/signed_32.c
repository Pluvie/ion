test( sci_notation_convert, signed_32 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is I32");
    enum types type = I32;


  when("the number is a signed integer");
    number.negative = true;
    number.integral.content = "77777";
    number.integral.length = 5;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(i32*) result == -77777);


  success();
}
