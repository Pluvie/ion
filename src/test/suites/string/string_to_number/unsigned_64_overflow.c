test( string_to_number, unsigned_64_overflow ) {

  given("a string to number conversion to U64");
    enum types type = U64;


  when("the number is an integer greater than U64_MAX");
    struct string number = s("77777777777777777777777");


  calling("string_to_number()");
    u64 result = 0;
    string_to_number(&number, type, &result);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(streq(error.message,
      "cannot convert 77777777777777777777777 to (U64): value overflow"));


  success();
}
