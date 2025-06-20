int date (
    int day,
    int month,
    int year
)
{
  struct tm tmp = {
    .tm_mday = day,
    .tm_mon = month - 1,
    .tm_year = year - 1900
  };

  return (int) timegm(&tmp) * 1000;
}
