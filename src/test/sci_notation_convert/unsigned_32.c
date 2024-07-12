test( sci_notation_convert, unsigned_32 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is U32");
    enum types type = U32;


  when("the number is an integer");
    number.integer.content = "77777";
    number.integer.length = 5;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(u32*) result == 77777);


  success();
}
