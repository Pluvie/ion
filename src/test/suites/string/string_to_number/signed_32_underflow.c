test( string_to_number, signed_32_underflow ) {

  given("a string to number conversion to I32");
    enum types type = I32;


  when("the number is an integer lesser than I32_MIN");
    struct string number = s("-77777777777");


  calling("string_to_number()");
    i32 result = 0;
    string_to_number(&number, type, &result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert -77777777777 to (I32): value overflow"));


  success();
}
