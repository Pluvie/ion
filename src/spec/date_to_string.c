spec( date_to_string ) {

  argument(int date_number);

  precondition("an integer representing a valid date expressed in milliseconds "\
               "elapsed since the Unix epoch");
    date_number = 915148800000; /* 01/01/1999 */

  must("return a `YYYY-MM-DD` formatted string of the given date");
    string date_string = date_to_string(date_number);
    string expected_string = s("1999-01-01");
    verify(eq(date_string, expected_string));

  must("utilize the global variable `__date_string` to hold the resulting string");
    verify(date_string.pointer == __date_string);

  success();
}
