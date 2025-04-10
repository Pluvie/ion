test( string_to_u16, contained ) {

  given("a string to u16 conversion");
  when("the number is contained within `u16` value bounds");
    string number = s("777");


  calling("string_to_u16()");
    u16 result = string_to_u16(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 777);


  success();
}
