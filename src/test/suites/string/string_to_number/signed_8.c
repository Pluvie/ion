test( string_to_number, signed_8 ) {

  given("a string to number conversion to I8");
    enum types type = I8;


  when("the number is a signed integer");
    struct string number = s("-77");


  calling("string_to_number()");
    i8 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == -77);


  success();
}
