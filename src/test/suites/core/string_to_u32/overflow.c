test( string_to_u32, overflow ) {

  given("a string to u32 conversion");
  when("the number overflows `u32` value bounds");
    string number = s("77777777777");


  calling("string_to_u32()");
    u32 result = string_to_u32(number);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(result == 0);
    verify(error_is("cannot convert `77777777777` to u32: value overflow"));


  success();
}
