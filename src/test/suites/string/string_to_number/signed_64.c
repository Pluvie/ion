test( string_to_number, signed_64 ) {

  given("a string to number conversion to I64");
    enum types type = I64;


  when("the number is a signed integer");
    struct string number = s("-77777777777");


  calling("string_to_number()");
    i64 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == -77777777777);


  success();
}
