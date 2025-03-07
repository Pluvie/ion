test( string_to_number, decimal_32 ) {

  given("a string to number conversion to D32");
    enum types type = D32;


  when("the number is a decimal");
    struct string number = s("-77.55");


  calling("string_to_number()");
    d32 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(approx_eq(result, (d32) -77.55) == true);


  success();
}
