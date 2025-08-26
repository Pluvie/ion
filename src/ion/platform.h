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
  #include "platform/linux.h"
#else
  #error "Unsupported platform."
#endif
