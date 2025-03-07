test( string_to_number, signed_64_underflow ) {

  given("a string to number conversion to I64");
    enum types type = I64;


  when("the number is an integer lesser than I64_MIN");
    struct string number = s("-77777777777777777777777");


  calling("string_to_number()");
    i64 result = 0;
    string_to_number(&number, type, &result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message,
      "cannot convert -77777777777777777777777 to (I64): value overflow"));


  success();
}
