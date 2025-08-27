string time_to_string (
    int time
)
{
  time_t time_in_seconds = time / 1000;
  int milliseconds = time - ((int) time_in_seconds * 1000);
  struct tm time_calendar;

  zero_out(__time_string, sizeof(__time_string));
  if (gmtime_r(&time_in_seconds, &time_calendar) == NULL)
    return (string) { 0 };

  strftime(__time_string, sizeof(__time_string),
    "%Y-%m-%d %H:%M:%S", &time_calendar);
  snprintf(__time_string + 19, 5, ".%03li", milliseconds);
  return (string) { .pointer = __time_string, .length = lengthof(__time_string) };
}
