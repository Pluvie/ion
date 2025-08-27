string date_to_string (
    int time
)
{
  time_t time_in_seconds = time / 1000;
  struct tm time_calendar;

  zero_out(__date_string, sizeof(__date_string));
  if (gmtime_r(&time_in_seconds, &time_calendar) == NULL)
    return (string) { 0 };

  strftime(__date_string, sizeof(__date_string), "%Y-%m-%d", &time_calendar);
  return (string) { .content = __date_string, .length = lengthof(__date_string) };
}
