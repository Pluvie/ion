test( string_to_i8, contained ) {

  given("a string to i8 conversion");
  when("the number is contained within `i8` value bounds");
    string number = s("123");


  calling("string_to_i8()");
    i8 result = string_to_i8(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 123);


  success();
}
