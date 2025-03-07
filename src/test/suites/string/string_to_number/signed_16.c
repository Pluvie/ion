test( string_to_number, signed_16 ) {

  given("a string to number conversion to I16");
    enum types type = I16;


  when("the number is a signed integer");
    struct string number = s("-777");


  calling("string_to_number()");
    i16 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == -777);


  success();
}
