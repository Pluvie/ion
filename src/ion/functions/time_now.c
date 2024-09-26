#ifdef ION_INCLUDED
static inline
#endif

i64 time_now (
    void
)
{
  struct timeval tmp;
  if(gettimeofday(&tmp, NULL) < 0)
    return 0;

  return ((i64) tmp.tv_sec * 1000) + ((i64) tmp.tv_usec / 1000);
}
