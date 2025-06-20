spec( time_now ) {

  must("return the current number of milliseconds elapsed since the Unix epoch");
    struct timeval tmp;
    gettimeofday(&tmp, NULL);
    int ms_since_unix_epoch = ((int) tmp.tv_sec * 1000) + ((int) tmp.tv_usec / 1000);
    int upper_threshold = ms_since_unix_epoch + 1000;
    int lower_threshold = ms_since_unix_epoch - 1000;

    int time_now_result = time_now();
    verify(time_now_result <= upper_threshold);
    verify(time_now_result >= lower_threshold);
}
