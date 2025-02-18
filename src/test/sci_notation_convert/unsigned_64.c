test( sci_notation_convert, unsigned_64 ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is U64");
    enum types type = U64;


  when("the number is an integer");
    number.integral.content = "77777777777";
    number.integral.length = 11;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(*(u64*) result == 77777777777);


  success();
}
