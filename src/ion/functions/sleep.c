void sleep (
    unsigned int milliseconds
)
{
#if platform(WINDOWS)
  Sleep(milliseconds);

#elif platform(LINUX)
  struct timespec ts;
  ts.tv_sec = milliseconds / 1000;
  ts.tv_nsec = (milliseconds % 1000) * 1000000;
  nanosleep(&ts, NULL);

#else
  #error "⚡️ION⚡️: This platform does not implement the `sleep` function."
#endif
}
