test( string_to_number, unsigned_64 ) {

  given("a string to number conversion to U64");
    enum types type = U64;


  when("the number is an integer");
    struct string number = s("77777777777");


  calling("string_to_number()");
    u64 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 77777777777);


  success();
}
