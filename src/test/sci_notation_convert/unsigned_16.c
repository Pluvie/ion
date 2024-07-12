test( sci_notation_convert, unsigned_16 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is U16");
    enum types type = U16;


  when("the number is an integer");
    number.integer.content = "1234";
    number.integer.length = 4;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(u16*) result == 1234);


  success();
}
