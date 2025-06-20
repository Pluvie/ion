spec( time_to_string ) {

  argument(int time);

  precondition("a greater than zero time, in milliseconds since the Unix epoch");
    time = 946684800001;

  must("return a `YYYY-MM-DD HH:mm:SS.LLL` formatted string of the given time");
    string time_string = time_to_string(time);
    verify(streq(time_string, s("2000-01-01 00:00:00.001")));

  must("utilize the global variable `__time_string` to hold the resulting string");
    verify(time_string.content == __time_string);
}
