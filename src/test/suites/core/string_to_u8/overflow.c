test( string_to_u8, overflow ) {

  given("a string to u8 conversion");
  when("the number overflows `u8` value bounds");
    string number = s("300");


  calling("string_to_u8()");
    u8 result = string_to_u8(number);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(result == 0);
    verify(error_is("cannot convert `300` to u8: value overflow"));


  success();
}
