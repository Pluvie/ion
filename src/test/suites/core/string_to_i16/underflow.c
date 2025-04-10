test( string_to_i16, underflow ) {

  given("a string to i16 conversion");
  when("the number underflows `i16` value bounds");
    string number = s("-77777");


  calling("string_to_i16()");
    i16 result = string_to_i16(number);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(result == 0);
    verify(error_is("cannot convert `-77777` to i16: value overflow"));


  success();
}
