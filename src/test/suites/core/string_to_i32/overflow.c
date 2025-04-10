test( string_to_i32, overflow ) {

  given("a string to i32 conversion");
  when("the number overflows `i32` value bounds");
    string number = s("77777777777");


  calling("string_to_i32()");
    i32 result = string_to_i32(number);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(result == 0);
    verify(error_is("cannot convert `77777777777` to i32: value overflow"));


  success();
}
