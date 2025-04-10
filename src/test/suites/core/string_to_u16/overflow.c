test( string_to_u16, overflow ) {

  given("a string to u16 conversion");
  when("the number overflows `u16` value bounds");
    string number = s("77777");


  calling("string_to_u16()");
    u16 result = string_to_u16(number);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(result == 0);
    verify(error_is("cannot convert `77777` to u16: value overflow"));


  success();
}
