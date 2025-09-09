#define LINUX   1
#define WINDOWS 2
#define MACOS   3

#define platform(name) PLATFORM == name

#if   defined(__linux__)
  #define PLATFORM LINUX
  #include "platform/linux.h"

#elif defined(__WIN32__)
  #define PLATFORM WINDOWS
  #include "platform/windows.h"

#elif defined(__APPLE__)
  #define PLATFORM MACOS
  #include "platform/macos.h"

#else
  #error "⚡️ION⚡️: Unsupported platform."
#endif
