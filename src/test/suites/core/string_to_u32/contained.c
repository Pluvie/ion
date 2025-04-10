test( string_to_u32, contained ) {

  given("a string to u32 conversion");
  when("the number is contained within `u32` value bounds");
    string number = s("777777");


  calling("string_to_u32()");
    u32 result = string_to_u32(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 777777);


  success();
}
