test( string_to_number, unsigned_16_overflow ) {

  given("a string to number conversion to U16");
    enum types type = U16;


  when("the number is an integer greater than U16_MAX");
    struct string number = s("77777");


  calling("string_to_number()");
    u16 result = 0;
    string_to_number(&number, type, &result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 77777 to (U16): value overflow"));


  success();
}
