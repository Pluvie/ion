test( string_to_number, decimal_64 ) {

  given("a string to number conversion to D64");
    enum types type = D64;


  when("the number is a decimal");
    struct string number = s("-77.55");


  calling("string_to_number()");
    d64 result = 0;
    string_to_number(&number, type, &result);


  must("convert the number correctly");
    verify(error.occurred == false);
    verify(approx_eq(result, (d64) -77.55) == true);


  success();
}
