test( string_to_number, unsigned_consistency ) {

  given("a string to number conversion to an unsigned type");
    enum types type = U64;


  when("the number is a negative integer");
    struct string number = s("-100");


  calling("string_to_number()");
    u64 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == -100);


  success();
}
