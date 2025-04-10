test( string_to_i64, contained ) {

  given("a string to i64 conversion");
  when("the number is contained within `i64` value bounds");
    string number = s("77777777");


  calling("string_to_i64()");
    i64 result = string_to_i64(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 77777777);


  success();
}
