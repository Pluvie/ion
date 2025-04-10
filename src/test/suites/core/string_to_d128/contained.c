test( string_to_d128, contained ) {

  given("a string to d128 conversion");
  when("the number is contained within `d128` value bounds");
    string number = s("-77.55");


  calling("string_to_d128()");
    d128 result = string_to_d128(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == -77.55);


  success();
}
