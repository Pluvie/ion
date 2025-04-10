test( string_to_u64, overflow ) {

  given("a string to u64 conversion");
  when("the number overflows `u64` value bounds");
    string number = s("77777777777777777777777");


  calling("string_to_u64()");
    u64 result = string_to_u64(number);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(result == 0);
    verify(error_is("cannot convert `77777777777777777777777` to u64: value overflow"));


  success();
}
