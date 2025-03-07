test( string_to_number, integer_consistency_exponent ) {

  given("a string to number conversion to I64");
    enum types type = I64;


  when("the number has a exponent");
    struct string number = s("100e33");


  calling("string_to_number()");
    i64 result = 0;
    string_to_number(&number, type, &result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message,
      "cannot convert 100e33 to (I64): invalid characters detected"));


  success();
}
