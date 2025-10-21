void chrono_start (
    struct chrono* c
)
{
#if platform(WINDOWS)
  /* The code below is untested and taken from
    https://stackoverflow.com/questions/20370920/convert-current-time-from-windows-to-unix-timestamp

  //Get the number of seconds since January 1, 1970 12:00am UTC
  const Int64 UNIX_TIME_START = 0x019DB1DED53E8000; //January 1, 1970 (start of Unix epoch) in "ticks"
  const Int64 TICKS_PER_SECOND = 10000000; //a tick is 100ns
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft); //returns ticks in UTC
  //Copy the low and high parts of FILETIME into a LARGE_INTEGER
  //This is so we can access the full 64-bits as an Int64 without causing an alignment fault
  LARGE_INTEGER li;
  li.LowPart  = ft.dwLowDateTime;
  li.HighPart = ft.dwHighDateTime;
  //Convert ticks since 1/1/1970 into seconds
  c->start = (li.QuadPart - UNIX_TIME_START) / TICKS_PER_SECOND;


  Alternatively we could use the GetSystemTime function and work our way using the
  wSecond and wMilliseconds fields.

  SYSTEMTIME t; GetSystemTime(&t);
  printf("The system time is: %02d:%02d:%02d.%03d\n",
           t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
  */

#elif platform(LINUX)
  struct timespec ts; clock_gettime(CLOCK_REALTIME, &ts);
  c->start = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;

#else
  #error "⚡️ION⚡️: This platform does not implement the `chrono_start` function."
#endif
}
