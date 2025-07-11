spec( date ) {

  argument(int day);
  argument(int month);
  argument(int year);

  precondition("an integer representing a valid calendar day");
  precondition("an integer representing a valid calendar month");
  precondition("an integer representing a valid calendar year");
    day = 25; month = 9; year = 1999;

  must("return the milliseconds elapsed since the Unix epoch up until that date");
    int elapsed_ms_unix_epoch = date(day, month, year);
    verify(elapsed_ms_unix_epoch == 938217600000);

  success();
}
