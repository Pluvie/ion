test( string_to_number, type_not_numeric ) {

  given("a string to number conversion to a not numeric type");
    enum types type = CHAR;


  when("the number is an integer");
    struct string number = s("-100");


  calling("string_to_number()");
    char result = 0;
    string_to_number(&number, type, &result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert -100 to (CHAR): type is not numeric"));


  success();
}
