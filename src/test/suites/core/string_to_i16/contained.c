test( string_to_i16, contained ) {

  given("a string to i16 conversion");
  when("the number is contained within `i16` value bounds");
    string number = s("555");


  calling("string_to_i16()");
    i16 result = string_to_i16(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 555);


  success();
}
