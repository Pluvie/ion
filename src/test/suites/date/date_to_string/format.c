test( date_to_string, format ) {

  given("a date");
    i64 date_number = date(1,1,1999);

  calling("date_to_string()");
    char* date_string = date_to_string(date_number);


  must("return the correct format");
    verify(streq(date_string, "1999-01-01"));


  success();
}
