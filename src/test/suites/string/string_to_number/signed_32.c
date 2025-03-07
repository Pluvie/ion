test( string_to_number, signed_32 ) {

  given("a string to number conversion to I32");
    enum types type = I32;


  when("the number is a signed integer");
    struct string number = s("-77777");


  calling("string_to_number()");
    i32 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == -77777);


  success();
}
