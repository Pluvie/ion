test( string_to_number, unsigned_8_overflow ) {

  given("a string to number conversion to U8");
    enum types type = U8;


  when("the number is an integer greater than U8_MAX");
    struct string number = s("300");


  calling("string_to_number()");
    u8 result = 0;
    string_to_number(&number, type, &result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 300 to (U8): value overflow"));


  success();
}
