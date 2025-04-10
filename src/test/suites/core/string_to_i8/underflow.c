test( string_to_i8, underflow ) {

  given("a string to i8 conversion");
  when("the number underflows `i8` value bounds");
    string number = s("-300");


  calling("string_to_i8()");
    i8 result = string_to_i8(number);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(result == 0);
    verify(error_is("cannot convert `-300` to i8: value overflow"));


  success();
}
