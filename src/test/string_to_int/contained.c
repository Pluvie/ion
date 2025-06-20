test( string_to_int, contained ) {

  given("a string to int conversion");
  when("the number is contained within `int` value bounds");
    string number = s("77777777");


  calling("string_to_int()");
    int result = string_to_int(number);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(result == 77777777);


  success();
}
