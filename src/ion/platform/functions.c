#if platform(LINUX)
  #include "linux/functions.c"
#else
  #error "Unsupported platform."
#endif
