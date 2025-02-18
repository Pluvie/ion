test( sci_notation_convert, unsigned_8 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is U8");
    enum types type = U8;


  when("the number is an integer");
    number.integral.content = "123";
    number.integral.length = 3;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(u8*) result == 123);


  success();
}
