#ifdef ION_INCLUDED
static inline
#endif

char* date_to_string (
    i64 time
)
{
  time_t time_in_seconds = time / 1000;
  struct tm time_calendar;

  memzero(__date_string, sizeof(__date_string));
  if (gmtime_r(&time_in_seconds, &time_calendar) == NULL)
    return NULL;

  strftime(__date_string, sizeof(__date_string), "%Y-%m-%d", &time_calendar);
  return (char*) __date_string;
}
