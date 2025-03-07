test( string_to_number, unsigned_32_overflow ) {

  given("a string to number conversion to U32");
    enum types type = U32;


  when("the number is an integer greater than U32_MAX");
    struct string number = s("77777777777");


  calling("string_to_number()");
    u32 result = 0;
    string_to_number(&number, type, &result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message, "cannot convert 77777777777 to (U32): value overflow"));


  success();
}
