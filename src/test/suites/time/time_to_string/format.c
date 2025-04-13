test( time_to_string, format ) {

  given("a time");
    i64 time_number = 946684800001;


  calling("time_to_string()");
    string time_string = time_to_string(time_number);


  must("return the correct format");
    verify(streq(time_string, s("2000-01-01 00:00:00.001")));


  success();
}
