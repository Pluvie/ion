test( string_to_dec, contained ) {

  given("a string to dec conversion");
  when("the number is contained within `dec` value bounds");
    string number = s("-77.55");


  calling("string_to_dec()");
    dec result = string_to_dec(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == -77.55);


  success();
}
