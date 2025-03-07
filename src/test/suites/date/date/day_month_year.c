test( date, day_month_year ) {

  given("a day, month and year");
    i64 day = 1;
    i64 month = 1;
    i64 year = 1999;

  calling("date()");
    i64 date_number = date(day, month, year);


  must("return the correct number");
    struct tm tmp;
    tmp.tm_mday = day;
    tmp.tm_mon = month - 1;
    tmp.tm_year = year - 1900;
    tmp.tm_sec = 0;
    tmp.tm_min = 0;
    tmp.tm_hour = 0;
    i64 expected_number = (i64) timegm(&tmp) * 1000;
    verify(date_number == expected_number);


  success();
}
