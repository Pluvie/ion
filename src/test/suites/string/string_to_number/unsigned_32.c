test( string_to_number, unsigned_32 ) {

  given("a string to number conversion to U32");
    enum types type = U32;


  when("the number is an integer");
    struct string number = s("77777");


  calling("string_to_number()");
    u32 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 77777);


  success();
}
