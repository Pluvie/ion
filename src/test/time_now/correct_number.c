test( time_now, correct_number ) {

  calling("time_now()");
    int now = time_now();


  must("return the correct number");
    int today = date_today();
    int yesterday = today - 1*DAY;
    int tomorrow = today + 1*DAY;
    verify(now >= today);
    verify(now >= yesterday);
    verify(now <= tomorrow);


  success();
}
