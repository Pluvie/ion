test( string_to_number, unsigned_16 ) {

  given("a string to number conversion to U16");
    enum types type = U16;


  when("the number is an integer");
    struct string number = s("1234");


  calling("string_to_number()");
    u16 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 1234);


  success();
}
