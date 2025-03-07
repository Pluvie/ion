test( string_to_number, unsigned_8 ) {

  given("a string to number conversion to U8");
    enum types type = U8;


  when("the number is an integer");
    struct string number = s("123");


  calling("string_to_number()");
    u8 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 123);


  success();
}
