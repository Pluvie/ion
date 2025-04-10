test( string_to_u64, contained ) {

  given("a string to u64 conversion");
  when("the number is contained within `u64` value bounds");
    string number = s("77777777777");


  calling("string_to_u64()");
    u64 result = string_to_u64(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 77777777777);


  success();
}
