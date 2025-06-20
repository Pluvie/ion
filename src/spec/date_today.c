spec( date_today ) {

  must("return the number of milliseconds elapsed since the Unix epoch up until today "\
       "at midnight");
    int today = date_today();

    time_t time_now = time(0);
    struct tm tmp;
    gmtime_r(&time_now, &tmp);
    tmp.tm_sec = 0;
    tmp.tm_min = 0;
    tmp.tm_hour = 0;
    int today_number = (int) timegm(&tmp) * 1000;

    verify(today_number == today);

  success();
}
