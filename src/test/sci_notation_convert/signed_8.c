test( sci_notation_convert, signed_8 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is I8");
    enum types type = I8;


  when("the number is a signed integer");
    number.negative = true;
    number.integer.content = "77";
    number.integer.length = 2;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(i8*) result == -77);


  success();
}
