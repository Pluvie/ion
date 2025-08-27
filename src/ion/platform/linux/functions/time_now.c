int time_now (
    void
)
{
  struct timeval tmp;
  if(gettimeofday(&tmp, NULL) < 0)
    return 0;

  return ((int) tmp.tv_sec * 1000) + ((int) tmp.tv_usec / 1000);
}
