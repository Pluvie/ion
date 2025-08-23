#define LINUX   1
#define WINDOWS 2
#define APPLE   3

#define platform(name) PLATFORM == name

#if   defined(__linux__)
  #define PLATFORM LINUX
#elif defined(__WIN32__)
  #define PLATFORM WINDOWS
#elif defined(__APPLE__)
  #define PLATFORM APPLE
#else
  #define PLATFORM 0
#endif

#if platform(LINUX)
  #include <errno.h>
  #include <fcntl.h>
  #include <stdbool.h>
  #include <stddef.h>
  #include <stdint.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <sys/socket.h>
  #include <sys/stat.h>
  #include <sys/time.h>
  #include <time.h>
  #include <unistd.h>
#else
  #error "Unsupported platform."
#endif
