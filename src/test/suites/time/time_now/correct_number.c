test( time_now, correct_number ) {

  calling("time_now()");
    i64 now = time_now();


  must("return the correct number");
    i64 today = date_today();
    i64 yesterday = today - 1*DAY;
    i64 tomorrow = today + 1*DAY;
    verify(now >= today);
    verify(now >= yesterday);
    verify(now <= tomorrow);


  success();
}
