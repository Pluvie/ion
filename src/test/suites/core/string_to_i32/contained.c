test( string_to_i32, contained ) {

  given("a string to i32 conversion");
  when("the number is contained within `i32` value bounds");
    string number = s("-7777");


  calling("string_to_i32()");
    i32 result = string_to_i32(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == -7777);


  success();
}
