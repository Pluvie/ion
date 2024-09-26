#ifdef ION_INCLUDED
static inline
#endif

i64 date (
    u32 day,
    u32 month,
    u32 year
)
{
  struct tm tmp = {
    .tm_mday = day,
    .tm_mon = month - 1,
    .tm_year = year - 1900
  };

  return (i64) timegm(&tmp) * 1000;
}
