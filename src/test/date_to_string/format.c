test( date_to_string, format ) {

  given("a date");
    int date_number = date(1,1,1999);


  calling("date_to_string()");
    string date_string = date_to_string(date_number);


  must("return the correct format");
    verify(streq(date_string, "1999-01-01"));


  success();
}
