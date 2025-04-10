test( string_to_u8, contained ) {

  given("a string to u8 conversion");
  when("the number is contained within `u8` value bounds");
    string number = s("123");


  calling("string_to_u8()");
    u8 result = string_to_u8(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 123);


  success();
}
