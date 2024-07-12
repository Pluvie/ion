test( sci_notation_convert, signed_16 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is I16");
    enum types type = I16;


  when("the number is a signed integer");
    number.negative = true;
    number.integer.content = "777";
    number.integer.length = 3;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(i16*) result == -777);


  success();
}
