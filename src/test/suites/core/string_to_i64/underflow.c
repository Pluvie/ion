test( string_to_i64, underflow ) {

  given("a string to i64 conversion");
  when("the number underflows `i64` value bounds");
    string number = s("-77777777777777777777777");


  calling("string_to_i64()");
    i64 result = string_to_i64(number);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(result == 0);
    verify(error_is("cannot convert `-77777777777777777777777` to i64: value overflow"));


  success();
}
