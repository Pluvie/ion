#ifdef ION_INCLUDED
static inline
#endif

i64 date_today (
    void
)
{
  time_t time_now = time(0);
  struct tm tmp;
  gmtime_r(&time_now, &tmp);
  tmp.tm_sec = 0;
  tmp.tm_min = 0;
  tmp.tm_hour = 0;

  return (i64) timegm(&tmp) * 1000;
}
