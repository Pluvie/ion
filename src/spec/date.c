spec( date ) {

  argument(int day);
  argument(int month);
  argument(int year);

  precondition("a valid calendar day, month and year representing a date");
    day = 25; month = 9; year = 1999;

  must("return the milliseconds elapsed since the Unix epoch up until the date");
    int elapsed_ms_unix_epoch = date(day, month, year);
    verify(elapsed_ms_unix_epoch == 938217600000);
}
