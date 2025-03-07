test( date_today, correct_number ) {

  calling("date_today()");
    i64 today = date_today();


  must("return the correct number");
    time_t time_now = time(0);
    struct tm tmp;
    gmtime_r(&time_now, &tmp);
    tmp.tm_sec = 0;
    tmp.tm_min = 0;
    tmp.tm_hour = 0;
    i64 today_number = (i64) timegm(&tmp) * 1000;

    verify(today_number == today);


  success();
}
