test( sci_notation_convert, type_not_numeric ) {

  given("a scientific notation conversion to a not numeric type");
    enum types type = CHAR;


  when("the number is an integer");
    struct sci_notation number = {
      .integral = s("100"),
    };


  calling("sci_notation_convert()");
    byte result[sizeof(char)] = { 0 };
    sci_notation_convert(&number, type, result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert to (CHAR): type is not numeric"));


  success();
}
