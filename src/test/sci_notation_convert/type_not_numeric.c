test( sci_notation_convert, type_not_numeric ) {

  given("a scientific notation number");
    struct sci_notation number = { 0 };


  when("the conversion type is not numeric");
    enum types type = CHAR;


  when("the number is an integer");
    number.integer.content = "100";
    number.integer.length = 3;


  calling("sci_notation_convert()");
    byte result[16] = { 0 };
    struct failure error = { 0 };
    sci_notation_convert(result, type, &number, &error);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert to (CHAR): type is not numeric"));


  success();
}
