test( string_to_number, signed_16_overflow ) {

  given("a string to number conversion to I16");
    enum types type = I16;


  when("the number is an integer greater than I16_MAX");
    struct string number = s("77777");


  calling("string_to_number()");
    i16 result = 0;
    string_to_number(&number, type, &result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 77777 to (I16): value overflow"));


  success();
}
