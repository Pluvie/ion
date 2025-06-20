spec( date_to_string ) {

  argument(int date_number);

  precondition("a valid date");
    date_number = date(1,1,1999);

  must("return a `YYYY-MM-DD` formatted string of the given date");
    string date_string = date_to_string(date_number);
    verify(streq(date_string, s("1999-01-01")));

  must("utilize the global variable `__date_string` to hold the resulting string");
    verify(date_string.content == __date_string);

  success();
}
