test( string_to_d32, contained ) {

  given("a string to d32 conversion");
  when("the number is contained within `d32` value bounds");
    string number = s("-77.55");


  calling("string_to_d32()");
    d32 result = string_to_d32(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == (d32) -77.55);


  success();
}
