test( string_to_int, overflow ) {

  given("a string to int conversion");
  when("the number overflows `int` value bounds");
    string number = s("77777777777777777777777");


  calling("string_to_int()");
    int result = string_to_int(number);


  must("fail to convert the number with a specific error");
    verify(error.occurred == true);
    verify(result == 0);
    verify(error_is("cannot convert `77777777777777777777777` to int: value overflow"));


  success();
}
