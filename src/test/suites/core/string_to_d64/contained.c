test( string_to_d64, contained ) {

  given("a string to d64 conversion");
  when("the number is contained within `d64` value bounds");
    string number = s("-77.55");


  calling("string_to_d64()");
    d64 result = string_to_d64(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == -77.55);


  success();
}
