test( date, day_month_year ) {

  given("a day, month and year");
    int day = 1;
    int month = 1;
    int year = 1999;

  calling("date()");
    int date_number = date(day, month, year);


  must("return the correct number");
    struct tm tmp;
    tmp.tm_mday = day;
    tmp.tm_mon = month - 1;
    tmp.tm_year = year - 1900;
    tmp.tm_sec = 0;
    tmp.tm_min = 0;
    tmp.tm_hour = 0;
    int expected_number = (int) timegm(&tmp) * 1000;
    verify(date_number == expected_number);


  success();
}
